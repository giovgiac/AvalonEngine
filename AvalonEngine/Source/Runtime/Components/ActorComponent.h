/**
 * ActorComponent.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Core/Object.h>

namespace Avalon
{
	class AActorComponent : public AObject
	{
	public:
		virtual void Destroy(void);

		virtual void Start(void);

		virtual void Tick(float DeltaTime);
	};
}