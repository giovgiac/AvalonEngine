/**
 * PrimitiveComponent.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Components/SceneComponent.h>

 // Windows Direct3D & COM
#include <d3d11_2.h>
#include <wrl.h>

namespace Avalon
{
	class APrimitiveComponent : public ASceneComponent
	{
	protected:
		TArray<SVertex> Vertices;
		TSharedPtr<class AMaterial> Material;
		XMCOLOR Color;
		Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBuffer;
		
	public:
		void SetMaterial(TSharedPtr<class AMaterial> InMaterial);

		virtual void Destroy(void) override;

		virtual void UpdateDimensions(void);

		XMCOLOR GetColor(void) const;

		class AMaterial* GetMaterial(void) const;

		TArray<SVertex>& GetVertices(void);

		ID3D11Buffer* GetVertexBuffer(void);

		ID3D11Buffer *const * GetVertexBufferAddressOf(void) const;

		ID3D11Buffer** GetVertexBufferAddress(void);
	};
}