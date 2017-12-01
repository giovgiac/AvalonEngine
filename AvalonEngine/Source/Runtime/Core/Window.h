/**
 * Window.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Core/Object.h>

namespace Avalon 
{
	enum class EWindowCreationError
	{
		SUCCESS						= 0,
		FAILED_TO_REGISTER_CLASS	= 1,
		FAILED_TO_CREATE_WINDOW		= 2
	};

	/** 
	 * AWindow Class
	 *
	 * This class is responsible for creating windows using the GLFW library.
	 *
	 */
	class AWindow : public AObject 
	{
	private:
		bool bFullscreen;
		bool bShouldClose;
		uint32 Width;
		uint32 Height;
		utf8* Title;
		void* Handle;

	public:
		/**
		 * AWindow Constructor
		 *
		 * This default constructor creates a window with the given width, height, title and whether is fullscreen.
		 *
		 * @param const uint32 InWidth: The width of the window.
		 * @param const uint32 InHeight: The height of the window.
		 * @param const utf8* InTitle: The title of the window.
		 * @param const bool InFullscreen: Whether the window is fullscreen or not.
		 *
		 */
		explicit AWindow(const uint32 InWidth, const uint32 InHeight, const utf8* InTitle, const bool InFullscreen);

		EWindowCreationError Start(void);

		void Destroy(void);

		void PollMessages(void);

		bool GetShouldClose(void) const;

		void* GetHandle(void) const;

		/**
		 * AWindow GetWidth
		 *
		 * This method gets the window current width.
		 *
		 * @return uint32: The window width.
		 *
		 */
		uint32 GetWidth(void) const;

		/**
		 * AWindow GetHeight
		 *
		 * This method gets the window current height.
		 *
		 * @return uint32: The window height.
		 *
		 */
		uint32 GetHeight(void) const;
	};

	extern AWindow* GetWindow(void);
}