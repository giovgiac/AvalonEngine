/**
 * MainEditor.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Core/Object.h>

#include <Windows.h>

namespace Avalon
{
	enum class EEditorMenu
	{
		FILE_MENU_NEW_SCENE				= 1,
		FILE_MENU_OPEN_SCENE			= 2,
		FILE_MENU_SAVE_CURRENT			= 3,
		FILE_MENU_SAVE_CURRENT_AS		= 4,
		FILE_MENU_SAVE_ALL				= 5,

		FILE_MENU_NEW_PROJECT			= 6,
		FILE_MENU_OPEN_PROJECT			= 7,

		PACKAGE_MENU_WINDOWS_32_BIT		= 8,
		PACKAGE_MENU_WINDOWS_64_BIT		= 9,

		FILE_MENU_EXIT					= 10,

		EDIT_MENU_UNDO					= 11,
		EDIT_MENU_REDO					= 12,

		EDIT_MENU_CUT					= 13,
		EDIT_MENU_COPY					= 14,
		EDIT_MENU_PASTE					= 15,
		EDIT_MENU_DUPLICATE				= 16,
		EDIT_MENU_DELETE				= 17,

		EDIT_MENU_PROJECT_SETTINGS		= 18,

		HELP_MENU_ABOUT_EDITOR			= 19
	};

	/**
	 * AMainEditor Class
	 *
	 * This class is responsible for creating windows using the GLFW library.
	 *
	 */
	class AMainEditor : public AObject
	{
	private:
		// Window Settings
		bool bShouldClose;
		uint32 Width;
		uint32 Height;
		utf8* Title;

		// Window Handles
		HWND Handle;
		HMENU Menu;

		// Runtime Objects
		class AWorld* World;

	public:
		/**
		 * AMainEditor Constructor
		 *
		 * This default constructor creates a window with the given width, height, title and whether is fullscreen.
		 *
		 * @param const uint32 InWidth: The width of the window.
		 * @param const uint32 InHeight: The height of the window.
		 * @param const utf8* InTitle: The title of the window.
		 *
		 */
		explicit AMainEditor(const uint32 InWidth, const uint32 InHeight, const utf8* InTitle);

		void Start(void);

		void Destroy(void);

		void Run(void);

		LRESULT CALLBACK WindowProcedure(HWND InHWND, UINT InMSG, WPARAM InWPARAM, LPARAM InLPARAM);

		bool GetShouldClose(void) const;

		HWND GetHandle(void) const;

		/**
		 * AMainEditor GetWidth
		 *
		 * This method gets the window current width.
		 *
		 * @return uint32: The window width.
		 *
		 */
		uint32 GetWidth(void) const;

		/**
		 * AMainEditor GetHeight
		 *
		 * This method gets the window current height.
		 *
		 * @return uint32: The window height.
		 *
		 */
		uint32 GetHeight(void) const;

	private:
		void AddMenus(HWND InHWND);

		void InitializeWindow(void);

		void InitializeWorld(void);

		void ProcessMenus(WPARAM InWPARAM);

		void PollMessages(void);

	};

	extern AMainEditor* GetMainEditor(void);
}