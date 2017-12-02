/**
 * Control.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Core/Types.h>

#include <Windows.h>

namespace Avalon
{
	enum class EAnchorPoint
	{
		CENTER			= 0,
		TOP_LEFT		= 1,
		TOP_RIGHT		= 2
	};

	class UControl
	{
	protected:
		// Dimensions
		float X;
		float Y;
		float Width;
		float Height;

		HWND Handle;
		
		EAnchorPoint AnchorPoint;

		TArray<UControl*> Children;
		UControl* Parent;

	public:
		void SetAnchor(const EAnchorPoint InAnchorPoint);

		void SetX(const float InX);

		void SetY(const float InY);

		void SetWidth(const float InWidth);

		void SetHeight(const float InHeight);

		HWND GetHandle(void) const;

		float GetX(void) const;

		float GetY(void) const;

		float GetWidth(void) const;

		float GetHeight(void) const;

		TArray<UControl*> GetChildren(void) const;

		UControl* GetParent(void) const;

		virtual void ConstructControl(HWND InParentHandle) = 0;

		virtual void ResizeControl(void);

		virtual void DestroyControl(void);

	protected:
		float GetRealX(void) const;

		float GetRealY(void) const;
	};
}