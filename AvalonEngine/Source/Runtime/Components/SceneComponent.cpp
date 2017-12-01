/**
 * SceneComponent.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "SceneComponent.h"

namespace Avalon
{
	void ASceneComponent::ConstructObject(void)
	{
		// Set Base Values
		Transform.Position = XMFLOAT2(0.0f, 0.0f);
		Transform.Rotation = 0.0f;
		Transform.Scale = XMFLOAT2(1.0f, 1.0f);
	}

	XMFLOAT2 ASceneComponent::GetComponentPosition(void) const
	{
		return Transform.Position;
	}

	float ASceneComponent::GetComponentRotation(void) const
	{
		return Transform.Rotation;
	}

	XMFLOAT2 ASceneComponent::GetComponentScale(void) const
	{
		return Transform.Scale;
	}

	STransform ASceneComponent::GetComponentTransform(void) const
	{
		return Transform;
	}

	void ASceneComponent::SetComponentTransform(const STransform InTransform)
	{
		Transform = InTransform;
	}
}