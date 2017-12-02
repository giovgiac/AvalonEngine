/**
 * SpriteComponent.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "SpriteComponent.h"

#include <Graphics/Material.h>
#include <Graphics/Texture.h>

namespace Avalon
{
	ASpriteComponent::ASpriteComponent(void)
	{

	}

	void ASpriteComponent::ConstructObject(void)
	{
		// Set Base Configuration
		Transform.Position = XMFLOAT2(0.0f, 0.0f);
		Transform.Rotation = 0.0f;
		Transform.Scale = XMFLOAT2(1.0f, 1.0f);
		Color = XMCOLOR(Colors::White);
		Material = nullptr;
		
		// Add Stock Vertices
		Vertices = TArray<SVertex>(6);
		Vertices[0] = { {  1.0f,  1.0f }, Color, { 1.0f, 0.0f } };
		Vertices[1] = { {  1.0f, -1.0f }, Color, { 1.0f, 1.0f } };
		Vertices[2] = { { -1.0f, -1.0f }, Color, { 0.0f, 1.0f } };
		Vertices[3] = { { -1.0f, -1.0f }, Color, { 0.0f, 1.0f } };
		Vertices[4] = { { -1.0f,  1.0f }, Color, { 0.0f, 0.0f } };
		Vertices[5] = { {  1.0f,  1.0f }, Color, { 1.0f, 0.0f } };
	}

	void ASpriteComponent::SetSprite(ATexture2D* InSprite)
	{
		GetMaterial()->SetDiffuse(InSprite);
	}

	void ASpriteComponent::UpdateDimensions(void)
	{
		ATexture2D* Sprite = GetMaterial()->GetDiffuse();

		if (Sprite)
		{
			// Update Texture Dimensions
			Sprite->UpdateDimensions();

			float Width = static_cast<float>(Sprite->GetWidth());
			float Height = static_cast<float>(Sprite->GetHeight());

			Vertices[0] = { {  Width / 2.0f,  Height / 2.0f }, Color,{ 1.0f, 0.0f } };
			Vertices[1] = { {  Width / 2.0f, -Height / 2.0f }, Color,{ 1.0f, 1.0f } };
			Vertices[2] = { { -Width / 2.0f, -Height / 2.0f }, Color,{ 0.0f, 1.0f } };
			Vertices[3] = { { -Width / 2.0f, -Height / 2.0f }, Color,{ 0.0f, 1.0f } };
			Vertices[4] = { { -Width / 2.0f,  Height / 2.0f }, Color,{ 0.0f, 0.0f } };
			Vertices[5] = { {  Width / 2.0f,  Height / 2.0f }, Color,{ 1.0f, 0.0f } };
		}
	}

	ATexture2D* ASpriteComponent::GetSprite(void) const
	{
		return GetMaterial()->GetDiffuse();
	}
}