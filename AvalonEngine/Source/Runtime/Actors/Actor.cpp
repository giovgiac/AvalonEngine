/**
 * Actor.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "Actor.h"

#include <Components/ActorComponent.h>
#include <Components/SpriteComponent.h>

#include <Core/World.h>

#include <Graphics/Material.h>
#include <Graphics/Texture.h>

namespace Avalon
{
	AActor::AActor(void)
	{

	}

	AActor::AActor(XMFLOAT2 InPosition, TSharedPtr<AMaterial> InMaterial)
	{
		STransform NewTransform;
		NewTransform.Position = InPosition;
		NewTransform.Rotation = 0.0f;
		NewTransform.Scale = XMFLOAT2(0.25f, 0.25f);

		ASpriteComponent* SpriteComponent = CreateDefaultSubobject<ASpriteComponent>("Test");
		SpriteComponent->SetMaterial(InMaterial);
		SpriteComponent->SetComponentTransform(NewTransform);
		Components.push_back(SpriteComponent);
	}

	void AActor::Destroy(void)
	{
		for (AActorComponent* Component : Components)
		{
			Component->Destroy();
			delete Component;
		}
	}

	void AActor::Start(void)
	{

	}

	void AActor::Tick(float InDeltaTime)
	{

	}

	void AActor::SetTransform(STransform InTransform)
	{
		Transform = InTransform;
	}

	void AActor::SetWorld(AWorld* InWorld)
	{
		World = InWorld;
	}

	AWorld* AActor::GetWorld(void) const
	{
		return World;
	}
}