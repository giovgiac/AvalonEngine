/**
 * Viewport.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Editor/Core/Control.h>

namespace Avalon
{
	class UViewport : public UControl
	{
	public:
		UViewport(UControl* InParent = nullptr, const float InX = 0.5f, const float InY = 0.5f, const float InWidth = 640.0f, const float InHeight = 480.0f, const EAnchorPoint InAnchorPoint = EAnchorPoint::CENTER);

		virtual void ConstructControl(HWND InParentHandle) override;
	};
}