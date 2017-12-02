/**
 * Textbox.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Editor/Core/Control.h>

namespace Avalon
{
	class UTextbox : public UControl
	{
	private:
		utf8* Text;

	public:
		UTextbox(UControl* InParent = nullptr, const float InX = 0.0f, const float InY = 0.0f, const float InWidth = 100.0f, const float InHeight = 20.0f, const EAnchorPoint InAnchorPoint = EAnchorPoint::CENTER);

		utf8* GetText(void);

		void SetText(const utf8* InText);

		virtual void ConstructControl(HWND InParentHandle) override;
	};
}