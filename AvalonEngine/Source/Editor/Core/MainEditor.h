/**
 * MainEditor.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Editor/Core/Control.h>

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
	 * UMainEditor Class
	 *
	 * This class is responsible for creating windows using the GLFW library.
	 *
	 */
	class UMainEditor : public UControl
	{
	private:
		// Window Settings
		bool bShouldClose;
		bool bResizing;
		utf8* Title;

		// Window Handles
		HMENU Menu;

		// Viewport Settings
		class UViewport* Viewport;

		// Runtime Objects
		class ATimer* Timer;
		class AWorld* World;

	public:
		/**
		 * UMainEditor Constructor
		 *
		 * This default constructor creates a window with the given width, height, title and whether is fullscreen.
		 *
		 * @param const uint32 InWidth: The width of the window.
		 * @param const uint32 InHeight: The height of the window.
		 * @param const utf8* InTitle: The title of the window.
		 *
		 */
		explicit UMainEditor(const float InWidth, const float InHeight, const utf8* InTitle);

		void Start(void);

		void Destroy(void);

		void Run(void);

		LRESULT CALLBACK WindowProcedure(HWND InHWND, UINT InMSG, WPARAM InWPARAM, LPARAM InLPARAM);

		bool GetShouldClose(void) const;

		class UViewport* GetViewport(void) const;

		virtual void ConstructControl(HWND InParentHandle) override;

	private:
		void AddControls(HWND InHWND);

		void AddMenus(HWND InHWND);

		void ResizeControls(void);

		void InitializeWindow(void);

		void InitializeWorld(void);

		void InitializeTimer(void);

		void ProcessMenus(WPARAM InWPARAM);

		void PollMessages(void);

	};

	extern UMainEditor* GetMainEditor(void);
}