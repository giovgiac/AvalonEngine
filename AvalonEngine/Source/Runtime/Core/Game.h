/**
 * Game.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Core/Object.h>

namespace Avalon 
{
	/**
	 * AGame Class
	 *
	 * This class is meant to be inherited from and to create the game using NEngine.
	 *
	 */
	class AGame : public AObject 
	{
	protected:
		class AWindow* Window;
		class AWorld* World;

	public:
		/**
		 * AGame BeforePlay
		 *
		 * This method is called immediately before play and the beginning of the main engine loop.
		 *
		 */
		virtual void BeforePlay(void) = 0;

		void Destroy(void);

		void Start(void);

		/**
		 * AGame Play
		 *
		 * This method is called to play the game and starts the main engine loop.
		 *
		 */
		void Play(void);

		/**
		 * AGame GetWindow
		 *
		 * This method gets a pointer to the window of this game.
		 *
		 * @return const AWindow*: A pointer to the window.
		 *
		 */
		class AWindow* GetWindow(void) const;

		/**
		 * AGame GetWorld
		 *
		 * This method gets the value of the world of this game.
		 *
		 * @return const AWorld&: A reference to the world.
		 *
		 */
		class AWorld* GetWorld(void) const;
	};
}