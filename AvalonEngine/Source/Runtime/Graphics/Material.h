/**
 * Material.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Core/Object.h>

namespace Avalon
{
	class AMaterial : public AObject
	{
	private:
		class ATexture2D* Diffuse;

	public:
		AMaterial(void);
	};
}