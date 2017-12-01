/**
 * Scene.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Core/Object.h>

namespace Avalon 
{
	/**
	 * AScene Class
	 *
	 * This class is responsible for creating the scenes, also called maps or levels.
	 *
	 */
	class AScene : public AObject 
	{
	private:
		TArray<class AActor*> Actors;
		class ACamera* Camera;
		XMFLOAT2 Size;

	public:
		/**
		 * AScene Constructor
		 *
		 * This default constructor initializes a scene with default width and height.
		 *
		 */
		AScene(void);

		/**
		 * AScene Constructor
		 *
		 * This constructor initializes a scene with the given size.
		 *
		 * @param const NVector& InSize: The size of the scene.
		 *
		 */
		explicit AScene(const XMFLOAT2 InSize);

		/**
		 * AScene AddActor
		 *
		 * This method adds a new actor to the scene.
		 *
		 * @param AActor* InObject: The actor to add to the scene.
		 *
		 */
		void AddActor(class AActor* InActor);

		void Destroy(void);

		void Start(void);

		/**
		 * AScene GetActors
		 *
		 * This method gets the actors of the scene.
		 *
		 * @return const TArray<AActor*>&: A reference to the array of actors.
		 *
		 */
		TArray<class AActor*> GetActors(void) const;

		/**
		 * AScene GetCamera
		 *
		 * This method gets the camera of the scene.
		 *
		 * @return const ACamera&: A reference to the camera.
		 *
		 */
		class ACamera* GetCamera(void) const;
	};
}