/**
 * Renderer.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "Renderer.h"

#include <Actors/Actor.h>

#include <Components/PrimitiveComponent.h>
#include <Components/SpriteComponent.h>

#include <Core/Window.h>

namespace Avalon 
{
	AD3DRenderer::AD3DRenderer(void)
	{
		
	}

	void AD3DRenderer::Destroy(void)
	{

	}

	void AD3DRenderer::Start(void)
	{
		HWND Handle = static_cast<HWND>(GetWindow()->GetHandle());
		
	}

	void AD3DRenderer::Render(const class AScene* InScene, const TArray<struct SRenderable*> InRenderables)
	{
		
	}
}