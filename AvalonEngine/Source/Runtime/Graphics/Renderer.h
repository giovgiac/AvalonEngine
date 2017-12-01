/**
 * Renderer.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Core/Object.h>

// Windows COM
#include <wrl.h>

namespace Avalon {
	struct SRenderable
	{
		uint32 Array;
		uint32 Buffer;
		class APrimitiveComponent* Component;
	};

	/**
	 * AD3DRenderer Class
	 *
	 * This class is responsible for rendering game scenes.
	 *
	 */
	class AD3DRenderer : public AObject {
	private:


	public:
		/**
		 * AD3DRenderer Constructor
		 *
		 * This default constructor initializes the renderer with the default shader.
		 *
		 */
		AD3DRenderer(void);

		void Destroy(void);

		void Start(void);

		/**
		 * AD3DRenderer Render
		 *
		 * This method renders (draws) a scene in the game, given the scene and it's vertex arrays.
		 *
		 * @param const AScene& InScene: The scene to render.
		 * @param const TArray<uint32>& Arrays: The vertex arrays of the objects.
		 *
		 */
		void Render(const class AScene* InScene, const TArray<struct SRenderable*> InRenderables);
	};
}