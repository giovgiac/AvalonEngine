/**
 * Transform.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <DirectXMath.h>

namespace Avalon
{
	struct STransform
	{
		DirectX::XMFLOAT2 Position;
		float Rotation;
		DirectX::XMFLOAT2 Scale;
	};
}