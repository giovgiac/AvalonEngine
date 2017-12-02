/**
 * Textbox.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "Textbox.h"

#include <CommCtrl.h>

namespace Avalon
{
	UTextbox::UTextbox(UControl* InParent, const float InX, const float InY, const float InWidth, const float InHeight, const EAnchorPoint InAnchorPoint)
	{
		Parent = InParent;
		X = InX;
		Y = InY;
		Width = InWidth;
		Height = InHeight;
		AnchorPoint = InAnchorPoint;
	}

	void UTextbox::ConstructControl(HWND InParentHandle)
	{
		float RealX = GetRealX();
		float RealY = GetRealY();

		if (InParentHandle)
		{
			Handle = CreateWindow(
				WC_EDIT,
				"...",
				WS_BORDER | WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
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
				WC_EDIT,
				"...",
				WS_BORDER | WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
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

	utf8* UTextbox::GetText(void)
	{
		if (Text)
		{
			delete Text;
		}

		int32 Length = GetWindowTextLength(Handle);
		Text = new utf8[Length + 1];
		GetWindowText(Handle, Text, Length + 1);
		
		return Text;
	}

	void UTextbox::SetText(const utf8* InText)
	{
		if (Text)
		{
			delete Text;
		}

		Text = _strdup(InText);
		SetWindowText(Handle, Text);
	}
}