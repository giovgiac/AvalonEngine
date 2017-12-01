/**
 * Game.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "Game.h"

#include <Core/Config.h>
#include <Core/Timer.h>
#include <Core/Window.h>
#include <Core/World.h>

#include <iostream>

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
		static ATimer* Timer = new ATimer;

		BeforePlay();

		// Reset Timer
		Timer->Reset();

		// Main Game Loop
		while (Window->GetShouldClose() == false)
		{
			World->Draw();
			Timer->Tick();
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