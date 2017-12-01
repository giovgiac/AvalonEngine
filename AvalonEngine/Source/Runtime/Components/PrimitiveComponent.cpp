/**
 * PrimitiveComponent.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "PrimitiveComponent.h"

namespace Avalon
{
	XMCOLOR APrimitiveComponent::GetColor(void) const
	{
		return Color;
	}

	TArray<SVertex> APrimitiveComponent::GetVertices(void) const
	{
		return Vertices;
	}
}