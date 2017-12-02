/**
 * Renderer.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "Renderer.h"

#include <Actors/Actor.h>

#include <Components/PrimitiveComponent.h>
#include <Components/SpriteComponent.h>

#include <Core/Window.h>

#include <Graphics/Camera.h>
#include <Graphics/Scene.h>
#include <Graphics/Material.h>

#include <Utils/File.h>

namespace Avalon 
{
	AD3DRenderer::AD3DRenderer(void)
	{
		
	}

	void AD3DRenderer::Destroy(void)
	{

	}

	void AD3DRenderer::Start(void)
	{		
		InitializeDirect3D();
		InitalizeSwapchain();
		InitializeRenderTarget();
		UpdateViewport();
	}

	void AD3DRenderer::InitializeDirect3D()
	{
		Microsoft::WRL::ComPtr<ID3D11Device> LegacyDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> LegacyDeviceContext;

		D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			0,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&LegacyDevice,
			nullptr,
			&LegacyDeviceContext
		);

		// Convert To DirectX 11.2
		LegacyDevice.As(&Device);
		LegacyDeviceContext.As(&DeviceContext);

		Microsoft::WRL::ComPtr<IDXGIAdapter> DXGIAdapter;
		Microsoft::WRL::ComPtr<IDXGIDevice1> DXGIDevice;

		Device.As(&DXGIDevice);
		DXGIDevice->GetAdapter(&DXGIAdapter);
		DXGIAdapter->GetParent(IID_PPV_ARGS(&Factory));
	}

	void AD3DRenderer::InitalizeSwapchain()
	{
		DXGI_SWAP_CHAIN_DESC1 SwapchainDesc = { 0 };
		SwapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		SwapchainDesc.BufferCount = 2;
		SwapchainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		SwapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
		SwapchainDesc.SampleDesc.Count = 1;

		HWND Handle = static_cast<HWND>(GetWindow()->GetHandle());
		Factory->CreateSwapChainForHwnd(
			Device.Get(),
			Handle,
			&SwapchainDesc,
			nullptr,
			nullptr,
			&Swapchain
		);
	}

	void AD3DRenderer::InitializeRenderTarget()
	{
		Microsoft::WRL::ComPtr<ID3D11Texture2D> BackBuffer;
		Swapchain->GetBuffer(0, IID_PPV_ARGS(&BackBuffer));

		Device->CreateRenderTargetView(BackBuffer.Get(), nullptr, &RenderTarget);
	}

	void AD3DRenderer::UpdateViewport()
	{
		D3D11_VIEWPORT Viewport = { 0 };
		Viewport.TopLeftX = 0.0f;
		Viewport.TopLeftY = 0.0f;
		Viewport.Width = static_cast<float>(GetWindow()->GetWidth());
		Viewport.Height = static_cast<float>(GetWindow()->GetHeight());

		DeviceContext->RSSetViewports(1, &Viewport);
	}

	void AD3DRenderer::LoadPrimitiveComponent(APrimitiveComponent* InComponent)
	{
		// Create Vertex Buffer
		D3D11_BUFFER_DESC BufferDesc = { 0 };
		BufferDesc.ByteWidth = static_cast<uint32>(sizeof(SVertex) * InComponent->GetVertices().size());
		BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA SubresourceData = { InComponent->GetVertices().data(), 0, 0 };
		Device->CreateBuffer(&BufferDesc, &SubresourceData, InComponent->GetVertexBufferAddress());

		if (InComponent->GetMaterial())
		{
			// Create Pixel Shader
			TArray<uint8>* PixelSource = ReadShader(InComponent->GetMaterial()->GetPixelFilename());
			Device->CreatePixelShader(
				PixelSource->data(),
				PixelSource->size(),
				nullptr,
				InComponent->GetMaterial()->GetPixelShaderAddress()
			);

			// Create Vertex Shader
			TArray<uint8>* VertexSource = ReadShader(InComponent->GetMaterial()->GetVertexFilename());
			Device->CreateVertexShader(
				VertexSource->data(),
				VertexSource->size(),
				nullptr,
				InComponent->GetMaterial()->GetVertexShaderAddress()
			);

			// Create Input Layout
			D3D11_INPUT_ELEMENT_DESC InputElementDesc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
			};
			Device->CreateInputLayout(
				InputElementDesc,
				ARRAYSIZE(InputElementDesc),
				VertexSource->data(),
				VertexSource->size(),
				InComponent->GetMaterial()->GetInputLayoutAddress()
			);

			// Cleanup Shader Sources
			delete PixelSource;
			delete VertexSource;
		}
	}

	void AD3DRenderer::Render(const AScene* InScene, const TArray<APrimitiveComponent*>& InComponents)
	{
		TArray<AActor*> Actors = InScene->GetActors();
		ACamera* Camera = InScene->GetCamera();
		
		// Clear Back Buffer
		DeviceContext->OMSetRenderTargets(1, RenderTarget.GetAddressOf(), nullptr);
		DeviceContext->ClearRenderTargetView(RenderTarget.Get(), Colors::DarkGray);

		// Get Matrices From Camera
		XMMATRIX ViewMatrix = Camera->GetView();
		XMMATRIX ProjectionMatrix = Camera->GetProjection();

		for (APrimitiveComponent* Component : InComponents)
		{
			uint32 Stride = sizeof(SVertex);
			uint32 Offset = 0;

			if (Component->GetMaterial())
			{
				// Bind Input Layout & Shaders
				DeviceContext->IASetInputLayout(Component->GetMaterial()->GetInputLayout());
				DeviceContext->VSSetShader(Component->GetMaterial()->GetVertexShader(), nullptr, 0);
				DeviceContext->PSSetShader(Component->GetMaterial()->GetPixelShader(), nullptr, 0);
			}

			// Bind Buffers
			DeviceContext->IASetVertexBuffers(0, 1, Component->GetVertexBufferAddressOf(), &Stride, &Offset);
			
			// Draw
			DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			DeviceContext->Draw(Component->GetVertices().size(), 0);
		}

		Swapchain->Present(0, 0);
	}
}