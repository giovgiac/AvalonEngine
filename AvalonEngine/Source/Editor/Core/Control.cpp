/**
 * Control.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "Control.h"

namespace Avalon
{
	void UControl::SetAnchor(const EAnchorPoint InAnchorPoint)
	{
		AnchorPoint = InAnchorPoint;
	}

	void UControl::SetX(const float InX)
	{
		X = InX;
	}

	void UControl::SetY(const float InY)
	{
		Y = InY;
	}

	void UControl::SetWidth(const float InWidth)
	{
		Width = InWidth;
	}

	void UControl::SetHeight(const float InHeight)
	{
		Height = InHeight;
	}

	HWND UControl::GetHandle(void) const
	{
		return Handle;
	}

	float UControl::GetX(void) const
	{
		return X;
	}

	float UControl::GetY(void) const
	{
		return Y;
	}

	float UControl::GetWidth(void) const
	{
		return Width;
	}

	float UControl::GetHeight(void) const
	{
		return Height;
	}

	TArray<UControl*> UControl::GetChildren(void) const
	{
		return Children;
	}

	UControl* UControl::GetParent(void) const
	{
		return Parent;
	}

	void UControl::ResizeControl(void)
	{
		for (UControl* Control : Children)
		{
			Control->ResizeControl();
		}

		DestroyWindow(Handle);
		if (GetParent())
		{
			ConstructControl(GetParent()->GetHandle());
		}
		else
		{
			ConstructControl(nullptr);
		}
	}

	void UControl::DestroyControl(void)
	{
		for (UControl* Control : Children)
		{
			Control->DestroyControl();
		}

		DestroyWindow(Handle);
	}

	float UControl::GetRealX(void) const
	{
		switch (AnchorPoint)
		{
		case EAnchorPoint::CENTER:
			if (Parent)
			{
				return (X * Parent->GetWidth() - Width / 2.0f);
			}

			break;
		case EAnchorPoint::TOP_LEFT:
			if (Parent)
			{
				return (X * Parent->GetWidth());
			}

			break;
		case EAnchorPoint::TOP_RIGHT:
			if (Parent)
			{
				return (X * Parent->GetWidth() - Width);
			}

			break;
		}

		return 0.0f;
	}

	float UControl::GetRealY(void) const
	{
		switch (AnchorPoint)
		{
		case EAnchorPoint::CENTER:
			if (Parent)
			{
				return (Y * Parent->GetHeight() - Height * 0.625f);
			}

			break;
		case EAnchorPoint::TOP_LEFT:
			if (Parent)
			{
				return (Y * Parent->GetHeight());
			}

			break;

		case EAnchorPoint::TOP_RIGHT:
			if (Parent)
			{
				return (Y * Parent->GetHeight());
			}

			break;
		}

		return 0.0f;
	}
}