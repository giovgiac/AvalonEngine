/**
 * World.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Actors/Actor.h>

namespace Avalon 
{
	/**
	 * AWorld
	 *
	 * This class is responsible for creating a world, the entity that renders a scene.
	 *
	 */
	class AWorld : public AObject 
	{
	private:
		TArray<class AActor*> Actors;
		TArray<struct SRenderable*> Renderables;
		TArray<uint32> Arrays;
		TArray<uint32> Buffers;
		class AD3DRenderer* Renderer;
		class AScene* Scene;

	public:
		/**
		 * AWorld Constructor
		 *
		 * This default constructor initializes a new world.
		 *
		 */
		AWorld(void);

		void Destroy(void);

		/**
		 * AWorld Draw
		 *
		 * This method calls upon the renderer to draw the current scene.
		 *
		 */
		void Draw(void);

		void Start(void);

		/**
		 * AWorld LoadScene
		 *
		 * This method loads a new scene into the world and the GPU.
		 *
		 * @param const AScene* InScene: The scene to load.
		 *
		 */
		void LoadScene(AScene* InScene);

		/**
		 * AWorld UnloadScene
		 *
		 * This method unloads the previously loaded scene from world and GPU.
		 *
		 */
		void UnloadScene(void);

		TArray<class AActor*> GetActors() const;

		/**
		 * AWorld GetScene
		 *
		 * This method returns the current scene.
		 *
		 * @return const AScene&: The current scene.
		 *
		 */
		class AScene* GetScene() const;

		template<typename T>
		T* SpawnActor(STransform Transform)
		{
			AActor* Actor = Cast<AActor>(new T());

			if (Actor)
			{
				// Set Transform

				AddActor(Actor);
				return Actor;
			}

			return nullptr;
		}

	private:
		void AddActor(class AActor* InActor);
	};
}