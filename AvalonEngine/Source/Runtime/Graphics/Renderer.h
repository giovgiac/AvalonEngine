/**
 * Renderer.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Core/Object.h>

// Windows Direct3D & COM
#include <d3d11_2.h>
#include <wrl.h>

namespace Avalon {
	/**
	 * AD3DRenderer Class
	 *
	 * This class is responsible for rendering game scenes.
	 *
	 */
	class AD3DRenderer : public AObject {
	private:
		Microsoft::WRL::ComPtr<ID3D11Device1> Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext1> DeviceContext;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> RenderTarget;
		Microsoft::WRL::ComPtr<ID3D11Buffer> TransformBuffer;
		Microsoft::WRL::ComPtr<ID3D11SamplerState> SamplerState;
		Microsoft::WRL::ComPtr<ID3D11BlendState> BlendState;
		Microsoft::WRL::ComPtr<IDXGIFactory2> Factory;
		Microsoft::WRL::ComPtr<IDXGISwapChain1> Swapchain;

	public:
		/**
		 * AD3DRenderer Constructor
		 *
		 * This default constructor initializes the renderer with the default shader.
		 *
		 */
		AD3DRenderer(void);

		void Destroy(void);

		void Start(void);

		void LoadPrimitiveComponent(class APrimitiveComponent* InComponent);

		/**
		 * AD3DRenderer Render
		 *
		 * This method renders (draws) a scene in the game, given the scene and it's vertex arrays.
		 *
		 * @param const AScene& InScene: The scene to render.
		 * @param const TArray<uint32>& Arrays: The vertex arrays of the objects.
		 *
		 */
		void Render(const class AScene* InScene, const TArray<class APrimitiveComponent*>& InComponents);

		void Resize(void);

		void UpdateViewport(void);

	private:
		void InitializeDirect3D(void);

		void InitializeSwapchain(void);

		void InitializeRenderTarget(void);

		void InitializeTransformBuffer(void);

		void InitializeStates(void);
	};
}