# Avalon Engine
The Avalon Engine is Game Engine being developed by Giovgiac. The Engine has basic graphics, audio and font rendering capabilities.

### Example Code
```cpp
/**
 * Main.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include <Actors/Actor.h>

#include <Core/Game.h>
#include <Core/World.h>

#include <Graphics/Scene.h>
#include <Graphics/Texture.h>

using namespace Avalon;

class MyGame : public AGame 
{
public:
	MyGame(void)
		: AGame() 
	{
	
	}

	void BeforePlay(void) override 
	{
		AScene* Scene = new AScene;

		// Create Textures
		ATexture2D* GokuTexture = new ATexture2D("goku.png");

		// Create Actors
		AActor* TestActor = new AActor();

		// Add Actors to Scene
		Scene->AddActor(TestActor);

		// Send Scene to World
		World->LoadScene(Scene);
	}
};

int main(void) {
	MyGame Game;

	Game.Start();
	Game.Play();
	Game.Destroy();
}
```