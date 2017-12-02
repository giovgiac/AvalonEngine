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
	private:
		virtual void ConstructObject(void);

	public:
		ASpriteComponent(void);

		void SetSprite(class ATexture2D* InSprite);

		virtual void UpdateDimensions(void) override;

		class ATexture2D* GetSprite(void) const;
	};
}