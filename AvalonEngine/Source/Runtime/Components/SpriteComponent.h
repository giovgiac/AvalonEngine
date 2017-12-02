/**
 * SpriteComponent.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Components/PrimitiveComponent.h>

namespace Avalon
{
	class ASpriteComponent : public APrimitiveComponent
	{
	protected:
		class ATexture2D* Sprite;

	private:
		virtual void ConstructObject(void);

	public:
		ASpriteComponent(void);

		void SetSprite(class ATexture2D* InSprite);

		class ATexture2D* GetSprite(void) const;
	};
}