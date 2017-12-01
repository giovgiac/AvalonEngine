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
		Microsoft::WRL::ComPtr<IDXGIFactory2> DXGIFactory;

		Device.As(&DXGIDevice);
		DXGIDevice->GetAdapter(&DXGIAdapter);
		DXGIAdapter->GetParent(IID_PPV_ARGS(&DXGIFactory));

		DXGI_SWAP_CHAIN_DESC1 SwapchainDesc = { 0 };
		SwapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		SwapchainDesc.BufferCount = 2;
		SwapchainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		SwapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
		SwapchainDesc.SampleDesc.Count = 1;

		HWND Handle = static_cast<HWND>(GetWindow()->GetHandle());
		DXGIFactory->CreateSwapChainForHwnd(
			Device.Get(),
			Handle,
			&SwapchainDesc,
			nullptr,
			nullptr,
			&Swapchain
		);
	}

	void AD3DRenderer::Render(const AScene* InScene, const TArray<SRenderable*> InRenderables)
	{
		Swapchain->Present(0, 0);
	}
}