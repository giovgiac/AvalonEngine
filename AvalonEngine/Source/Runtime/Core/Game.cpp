/**
 * Game.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "Game.h"

#include <Core/Config.h>
#include <Core/Window.h>
#include <Core/World.h>

namespace Avalon 
{
	void AGame::Destroy(void)
	{
		// Destroy Worlds
		World->Destroy();
		delete World;

		// Destroy Windows
		Window->Destroy();
		delete Window;
	}

	void AGame::Start(void)
	{
		// Create Windows
		Window = new AWindow(DefaultWindowWidth, DefaultWindowHeight, DefaultWindowTitle, DefaultWindowFullscreen);
		Window->Start();
		// TODO: Catch Window Creation Errors

		// Create Worlds
		World = new AWorld();
		World->Start();
		// TODO: Catch World Creation Errors
	}

	void AGame::Play(void)
	{
		BeforePlay();

		// Main Game Loop
		while (Window->GetShouldClose() == false)
		{
			World->Draw();
			Window->PollMessages();
		}
	}

	AWindow* AGame::GetWindow(void) const
	{
		return Window;
	}

	AWorld* AGame::GetWorld(void) const
	{
		return World;
	}
}