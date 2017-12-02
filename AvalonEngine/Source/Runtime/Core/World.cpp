/**
 * World.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "World.h"

#include <Components/PrimitiveComponent.h>
#include <Graphics/Renderer.h>
#include <Graphics/Scene.h>

namespace Avalon 
{
	AWorld::AWorld(void)
		: 
		Scene(nullptr),
		Renderer(nullptr) 
	{
		
	}

	void AWorld::Destroy(void)
	{
		// Destroy Scene
		if (Scene)
		{
			UnloadScene();
		}

		// Destroy Renderer
		Renderer->Destroy();
		delete Renderer;
	}

	void AWorld::Draw(void) 
	{
		Renderer->Render(Scene, PrimitiveComponents);
	}

	void AWorld::Start(void)
	{
		// Create Renderer
		Renderer = new AD3DRenderer();
		Renderer->Start();
	}

	void AWorld::LoadScene(AScene* InScene)
	{
		if (Scene)
		{
			UnloadScene();
		}
		else
		{
			Scene = InScene;
			Scene->Start();
		}

		for (AActor* Actor : InScene->GetActors())
		{
			AddActor(Actor);
		}
	}

	void AWorld::UnloadScene(void) 
	{
		Scene->Destroy();
		delete Scene;
	}

	void AWorld::AddActor(AActor* InActor)
	{
		TArray<APrimitiveComponent*> Components = InActor->GetComponentsByClass<APrimitiveComponent>();

		// Buffer Actor Geometry to GPU
		for (APrimitiveComponent* Component : Components)
		{
			Renderer->LoadPrimitiveComponent(Component);

			PrimitiveComponents.push_back(Component);
		}

		Actors.push_back(InActor);
	}

	TArray<AActor*> AWorld::GetActors() const
	{
		return Actors;
	}

	AScene* AWorld::GetScene() const
	{
		return Scene;
	}
}