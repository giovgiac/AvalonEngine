/**
 * Vertex.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <DirectXMath.h>
#include <DirectXPackedVector.h>

namespace Avalon 
{
	/**
	 * Vertex Struct
	 *
	 * This data type is understood by the GPU and contains the properties necessary to draw a vertex.
	 *
	 */
	struct SVertex 
	{
		DirectX::XMFLOAT2 Position;
		DirectX::PackedVector::XMCOLOR Color;
		DirectX::XMFLOAT2 TexCoord;
	};
}