/**
 * PrimitiveComponent.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Components/SceneComponent.h>

namespace Avalon
{
	class APrimitiveComponent : public ASceneComponent
	{
	protected:
		TArray<SVertex> Vertices;
		XMCOLOR Color;
		
	public:
		XMCOLOR GetColor(void) const;

		TArray<SVertex> GetVertices(void) const;
	};
}