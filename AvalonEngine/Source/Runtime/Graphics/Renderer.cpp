/**
 * Renderer.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "Renderer.h"

// Runtime Includes
#include <Actors/Actor.h>

#include <Components/PrimitiveComponent.h>
#include <Components/SpriteComponent.h>

#include <Core/Config.h>
#include <Core/Window.h>

#include <Graphics/Camera.h>
#include <Graphics/Scene.h>
#include <Graphics/Material.h>
#include <Graphics/Texture.h>

#include <Utils/File.h>

#include <WICTextureLoader.h>

// Editor Includes
#include <Editor/Core/MainEditor.h>

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
		InitializeTransformBuffer();
		InitializeStates();
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

		HWND Handle = nullptr;
		if (GetWindow())
		{
			Handle = static_cast<HWND>(GetWindow()->GetHandle());
		}
		else if (GetMainEditor())
		{
			Handle = GetMainEditor()->GetHandle();
		}

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

	void AD3DRenderer::InitializeTransformBuffer(void)
	{
		D3D11_BUFFER_DESC BufferDesc = { 0 };
		BufferDesc.ByteWidth = sizeof(XMMATRIX);
		BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		Device->CreateBuffer(&BufferDesc, nullptr, &TransformBuffer);
		DeviceContext->VSSetConstantBuffers(0, 1, TransformBuffer.GetAddressOf());
	}

	void AD3DRenderer::InitializeStates(void)
	{
		D3D11_BLEND_DESC BlendStateDesc;
		BlendStateDesc.AlphaToCoverageEnable = false;
		BlendStateDesc.IndependentBlendEnable = false;
		
		for (uint32 i = 0; i < 8; i++)
		{
			BlendStateDesc.RenderTarget[i].BlendEnable = true;
			BlendStateDesc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			BlendStateDesc.RenderTarget[i].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			BlendStateDesc.RenderTarget[i].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			BlendStateDesc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ZERO;
			BlendStateDesc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ZERO;
			BlendStateDesc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
			BlendStateDesc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		}

		Device->CreateBlendState(&BlendStateDesc, &BlendState);

		D3D11_SAMPLER_DESC SamplerDesc;
		SamplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		SamplerDesc.MaxAnisotropy = 16;
		SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		SamplerDesc.BorderColor[0] = 0.0f;
		SamplerDesc.BorderColor[1] = 0.0f;
		SamplerDesc.BorderColor[2] = 0.0f;
		SamplerDesc.BorderColor[3] = 0.0f;
		SamplerDesc.MinLOD = 0.0f;
		SamplerDesc.MaxLOD = FLT_MAX;
		SamplerDesc.MipLODBias = 0.0f;

		Device->CreateSamplerState(&SamplerDesc, &SamplerState);
	}

	void AD3DRenderer::UpdateViewport()
	{
		D3D11_VIEWPORT Viewport = { 0 };
		Viewport.TopLeftX = 0.0f;
		Viewport.TopLeftY = 0.0f;
		if (GetWindow())
		{
			Viewport.Width = static_cast<float>(GetWindow()->GetWidth());
			Viewport.Height = static_cast<float>(GetWindow()->GetHeight());
		}
		else if (GetMainEditor())
		{
			Viewport.Width = static_cast<float>(GetMainEditor()->GetWidth());
			Viewport.Height = static_cast<float>(GetMainEditor()->GetHeight());
		}
		else
		{
			Viewport.Width = static_cast<float>(DefaultWindowWidth);
			Viewport.Height = static_cast<float>(DefaultWindowHeight);
		}

		DeviceContext->RSSetViewports(1, &Viewport);
	}

	void AD3DRenderer::LoadPrimitiveComponent(APrimitiveComponent* InComponent)
	{
		if (InComponent->GetMaterial())
		{
			// Load Texture
			if (InComponent->GetMaterial()->GetDiffuse())
			{
				if (InComponent->GetMaterial()->GetDiffuse()->GetTexture() == nullptr)
				{
					CreateWICTextureFromFile(
						Device.Get(),
						nullptr,
						InComponent->GetMaterial()->GetDiffuse()->GetFilename(),
						nullptr,
						InComponent->GetMaterial()->GetDiffuse()->GetTextureAddress(),
						0
					);
				}
			}

			// Shader Code Arrays
			TArray<uint8>* PixelSource = nullptr;
			TArray<uint8>* VertexSource = nullptr;

			// Create Pixel Shader
			if (InComponent->GetMaterial()->GetPixelShader() == nullptr)
			{
				PixelSource = ReadShader(InComponent->GetMaterial()->GetPixelFilename());
				
				if (PixelSource)
				{
					Device->CreatePixelShader(
						PixelSource->data(),
						PixelSource->size(),
						nullptr,
						InComponent->GetMaterial()->GetPixelShaderAddress()
					);
				}
			}

			// Create Vertex Shader
			if (InComponent->GetMaterial()->GetVertexShader() == nullptr)
			{
				VertexSource = ReadShader(InComponent->GetMaterial()->GetVertexFilename());

				if (VertexSource)
				{
					Device->CreateVertexShader(
						VertexSource->data(),
						VertexSource->size(),
						nullptr,
						InComponent->GetMaterial()->GetVertexShaderAddress()
					);
				}
			}

			// Create Input Layout
			if (InComponent->GetMaterial()->GetInputLayout() == nullptr)
			{
				D3D11_INPUT_ELEMENT_DESC InputElementDesc[] =
				{
					{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
					{ "COLOR", 0, DXGI_FORMAT_B8G8R8A8_UNORM, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0 },
					{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
				};

				if (VertexSource)
				{
					Device->CreateInputLayout(
						InputElementDesc,
						ARRAYSIZE(InputElementDesc),
						VertexSource->data(),
						VertexSource->size(),
						InComponent->GetMaterial()->GetInputLayoutAddress()
					);
				}
			}

			// Update Texture Width & Height
			InComponent->UpdateDimensions();

			// Create Vertex Buffer
			D3D11_BUFFER_DESC BufferDesc = { 0 };
			BufferDesc.ByteWidth = static_cast<uint32>(sizeof(SVertex) * InComponent->GetVertices().size());
			BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

			D3D11_SUBRESOURCE_DATA SubresourceData = { InComponent->GetVertices().data(), 0, 0 };
			Device->CreateBuffer(&BufferDesc, &SubresourceData, InComponent->GetVertexBufferAddress());

			// Cleanup Shader Sources
			if (PixelSource)
			{
				delete PixelSource;
			}

			if (VertexSource)
			{
				delete VertexSource;
			}
		}
	}

	void AD3DRenderer::Render(const AScene* InScene, const TArray<APrimitiveComponent*>& InComponents)
	{
		// Clear Back Buffer
		DeviceContext->OMSetRenderTargets(1, RenderTarget.GetAddressOf(), nullptr);
		DeviceContext->ClearRenderTargetView(RenderTarget.Get(), Colors::DarkGray);

		if (InScene)
		{
			ACamera* Camera = InScene->GetCamera();

			// Get Matrices From Camera
			XMMATRIX ViewMatrix = Camera->GetView();
			XMMATRIX ProjectionMatrix = Camera->GetProjection();

			for (APrimitiveComponent* Component : InComponents)
			{
				uint32 Stride = sizeof(SVertex);
				uint32 Offset = 0;

				// Get Component Transform
				STransform Transform = Component->GetComponentTransform();

				if (Component->GetMaterial())
				{
					// Bind Input Layout & Shaders
					DeviceContext->IASetInputLayout(Component->GetMaterial()->GetInputLayout());
					DeviceContext->VSSetShader(Component->GetMaterial()->GetVertexShader(), nullptr, 0);
					DeviceContext->PSSetShader(Component->GetMaterial()->GetPixelShader(), nullptr, 0);
				}

				// Bind Buffers
				DeviceContext->IASetVertexBuffers(0, 1, Component->GetVertexBufferAddressOf(), &Stride, &Offset);

				// Update Transform
				XMMATRIX TranslateMatrix = XMMatrixTranslation(Transform.Position.x, Transform.Position.y, 0.0f);
				XMMATRIX RotateMatrix = XMMatrixRotationZ(Transform.Rotation);
				XMMATRIX ScaleMatrix = XMMatrixScaling(Transform.Scale.x, Transform.Scale.y, 1.0f);
				XMMATRIX WorldMatrix = ScaleMatrix * RotateMatrix * TranslateMatrix;
				XMMATRIX TransformMatrix = WorldMatrix * ViewMatrix * ProjectionMatrix;

				// Update Transform Buffer
				DeviceContext->UpdateSubresource(TransformBuffer.Get(), 0, 0, &TransformMatrix, 0, 0);

				// Send Diffuse Texture To Pixel Shader
				DeviceContext->PSSetShaderResources(0, 1, Component->GetMaterial()->GetDiffuse()->GetTextureAddressOf());

				// Set States
				DeviceContext->PSSetSamplers(0, 1, SamplerState.GetAddressOf());
				DeviceContext->OMSetBlendState(BlendState.Get(), 0, 0xFFFFFFFF);

				// Draw
				DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				DeviceContext->Draw(static_cast<uint32>(Component->GetVertices().size()), 0);
			}
		}

		Swapchain->Present(0, 0);
	}
}