/**
 * SceneComponent.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Components/ActorComponent.h>

namespace Avalon
{
	class ASceneComponent : public AActorComponent
	{
	protected:
		STransform Transform;

	private:
		virtual void ConstructObject(void) override;

	public:
		XMFLOAT2 GetComponentPosition(void) const;

		float GetComponentRotation(void) const;

		XMFLOAT2 GetComponentScale(void) const;

		STransform GetComponentTransform(void) const;

		void SetComponentPosition(const XMFLOAT2 InPosition);

		void SetComponentRotation(const float InRotation);

		void SetComponentScale(const XMFLOAT2 InScale);

		void SetComponentTransform(const STransform InTransform);
	};
}