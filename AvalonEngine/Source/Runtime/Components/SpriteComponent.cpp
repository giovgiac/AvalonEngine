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
		:
		Sprite(nullptr)
	{

	}

	void ASpriteComponent::ConstructObject(void)
	{
		// Set Base Configuration
		Transform.Position = XMFLOAT2(0.0f, 0.0f);
		Transform.Rotation = 0.0f;
		Transform.Scale = XMFLOAT2(1.0f, 1.0f);
		Color = XMCOLOR(Colors::Red);
		Material = nullptr;
		Sprite = nullptr;
		
		// Add Stock Vertices
		/*
		Vertices = TArray<SVertex>(4);
		Vertices[0] = { XMFLOAT2(-1.0f,  1.0f), Color, XMFLOAT2(0.0f, 1.0f) };
		Vertices[1] = { XMFLOAT2(-1.0f, -1.0f), Color, XMFLOAT2(0.0f, 0.0f) };
		Vertices[2] = { XMFLOAT2( 1.0f, -1.0f), Color, XMFLOAT2(1.0f, 0.0f) };
		Vertices[3] = { XMFLOAT2( 1.0f,  1.0f), Color, XMFLOAT2(1.0f, 1.0f) };
		*/
		Vertices = TArray<SVertex>(6);
		Vertices[0] = { {  1.00f,  1.00f }, Color, { 0.0f, 0.0f } };
		Vertices[1] = { {  1.00f, -1.00f }, Color, { 0.0f, 0.0f } };
		Vertices[2] = { { -1.00f, -1.00f }, Color, { 0.0f, 0.0f } };
		Vertices[3] = { { -1.00f, -1.00f }, Color, { 0.0f, 0.0f } };
		Vertices[4] = { { -1.00f,  1.00f }, Color, { 0.0f, 0.0f } };
		Vertices[5] = { {  1.00f,  1.00f }, Color, { 0.0f, 0.0f } };
	}

	void ASpriteComponent::SetSprite(ATexture2D* InSprite)
	{
		Sprite = InSprite;

		/*
		if (Sprite)
		{
			float Width = static_cast<float>(Sprite->GetWidth());
			float Height = static_cast<float>(Sprite->GetHeight());

			Vertices[0] = { XMFLOAT2(-Width / 2.0f,  Height / 2.0f), Color, XMFLOAT2(0.0f, 1.0f) };
			Vertices[1] = { XMFLOAT2(-Width / 2.0f, -Height / 2.0f), Color, XMFLOAT2(0.0f, 0.0f) };
			Vertices[2] = { XMFLOAT2( Width / 2.0f, -Height / 2.0f), Color, XMFLOAT2(1.0f, 0.0f) };
			Vertices[3] = { XMFLOAT2( Width / 2.0f,  Height / 2.0f), Color, XMFLOAT2(1.0f, 1.0f) };
		}
		*/
	}

	ATexture2D* ASpriteComponent::GetSprite(void) const
	{
		return Sprite;
	}
}