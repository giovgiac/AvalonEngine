# Avalon Engine
The Avalon Engine is a Game Engine being developed by Giovgiac. The Engine has basic graphics, audio and font rendering capabilities.

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
#include <Graphics/Material.h>
#include <Graphics/Texture.h>

using namespace Avalon;

class MyGame : public AGame 
{
public:
	void BeforePlay(void) override 
	{
		AScene* Scene = new AScene;

		// Create Textures
		ATexture2D* GokuTexture1 = new ATexture2D("goku.png");
		ATexture2D* GokuTexture2 = new ATexture2D("goku.png");

		// Create Materials
		AMaterial* TestMaterial1 = new AMaterial();
		TestMaterial1->SetDiffuse(GokuTexture1);

		AMaterial* TestMaterial2 = new AMaterial();
		TestMaterial2->SetDiffuse(GokuTexture2);

		// Create Actors
		AActor* TestActor1 = new AActor(XMFLOAT2( 000.0f,  000.0f), TestMaterial1);
		AActor* TestActor2 = new AActor(XMFLOAT2( 200.0f,  100.0f), TestMaterial1);
		AActor* TestActor3 = new AActor(XMFLOAT2(-200.0f, -200.0f), TestMaterial2);

		// Add Actors to Scene
		Scene->AddActor(TestActor1);
		Scene->AddActor(TestActor2);
		Scene->AddActor(TestActor3);

		// Send Scene to World
		World->LoadScene(Scene);
	}
};

int main(void)
{
	MyGame* Game = new MyGame;

	Game->Start();
	Game->Play();
	Game->Destroy();

	delete Game;
	return EXIT_SUCCESS;
}
```