/**
 * Texture.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "Texture.h"

namespace Avalon {
	ATexture2D::ATexture2D(const utf8* InFilename)
	{
		
	}

	uint32 ATexture2D::GetWidth(void) const 
	{ 
		return Width;
	}

	uint32 ATexture2D::GetHeight(void) const 
	{
		return Height;
	}
}