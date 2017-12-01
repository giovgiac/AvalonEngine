/**
 * Scene.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "Scene.h"

#include <Actors/Actor.h>
#include <Core/Config.h>
#include <Graphics/Camera.h>

namespace Avalon 
{
	AScene::AScene(void)
		: 
		Camera(nullptr),
		Size(DefaultSceneWidth, DefaultSceneHeight)
	{

	}

	AScene::AScene(const XMFLOAT2 InSize)
		: 
		Camera(nullptr),
		Size(InSize) 
	{

	}

	void AScene::AddActor(AActor* InActor)
	{
		Actors.push_back(InActor);
	}

	void AScene::Destroy(void)
	{
		// Destroy Actors
		for (AActor* Actor : Actors)
		{
			Actor->Destroy();
			delete Actor;
		}

		// Destroy Camera
		Camera->Destroy();
		delete Camera;
	}

	void AScene::Start(void)
	{
		// Create Camera
		Camera = new ACamera(Size.x, Size.y);
		Camera->Start();
	}

	TArray<AActor*> AScene::GetActors(void) const
	{
		return Actors;
	}

	ACamera* AScene::GetCamera(void) const
	{
		return Camera;
	}
}