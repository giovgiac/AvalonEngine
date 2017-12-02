/**
 * PrimitiveComponent.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "PrimitiveComponent.h"

#include <Graphics/Material.h>

namespace Avalon
{
	void APrimitiveComponent::SetMaterial(AMaterial* InMaterial)
	{
		Material = InMaterial;
	}

	XMCOLOR APrimitiveComponent::GetColor(void) const
	{
		return Color;
	}

	AMaterial* APrimitiveComponent::GetMaterial(void) const
	{
		return Material;
	}

	TArray<SVertex>& APrimitiveComponent::GetVertices(void)
	{
		return Vertices;
	}

	ID3D11Buffer* APrimitiveComponent::GetVertexBuffer(void)
	{
		return VertexBuffer.Get();
	}

	ID3D11Buffer *const * APrimitiveComponent::GetVertexBufferAddressOf(void) const
	{
		return VertexBuffer.GetAddressOf();
	}

	ID3D11Buffer** APrimitiveComponent::GetVertexBufferAddress(void)
	{
		return &VertexBuffer;
	}
}