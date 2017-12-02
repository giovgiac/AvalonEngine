/**
 * Viewport.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "Viewport.h"

#include <CommCtrl.h>

namespace Avalon
{
	UViewport::UViewport(UControl* InParent, const float InX, const float InY, const float InWidth, const float InHeight, const EAnchorPoint InAnchorPoint)
	{
		Parent = InParent;
		X = InX;
		Y = InY;
		Width = InWidth;
		Height = InHeight;
		AnchorPoint = InAnchorPoint;
	}

	void UViewport::ConstructControl(HWND InParentHandle)
	{
		float RealX = GetRealX();
		float RealY = GetRealY();

		if (InParentHandle)
		{
			Handle = CreateWindow(
				WC_DIALOG,
				"...",
				WS_BORDER | WS_VISIBLE | WS_CHILD,
				RealX,
				RealY,
				Width,
				Height,
				InParentHandle,
				NULL,
				NULL,
				NULL
			);
		}
		else
		{
			Handle = CreateWindow(
				WC_DIALOG,
				"...",
				WS_BORDER | WS_VISIBLE | WS_CHILD,
				RealX,
				RealY,
				Width,
				Height,
				Parent->GetHandle(),
				NULL,
				NULL,
				NULL
			);
		}
	}
}