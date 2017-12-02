/**
 * MainEditor.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "MainEditor.h"

#include <Actors/Actor.h>

#include <Core/Window.h>
#include <Core/World.h>

#include <Graphics/Material.h>
#include <Graphics/Scene.h>
#include <Graphics/Texture.h>

static Avalon::AMainEditor* MainEditor = nullptr;

LRESULT CALLBACK WinProcedure(HWND InHWND, UINT InMSG, WPARAM InWPARAM, LPARAM InLPARAM)
{
	if (MainEditor)
	{
		return MainEditor->WindowProcedure(InHWND, InMSG, InWPARAM, InLPARAM);
	}
	else
	{
		return DefWindowProc(InHWND, InMSG, InWPARAM, InLPARAM);
	}
}

namespace Avalon
{
	AMainEditor::AMainEditor(const uint32 InWidth, const uint32 InHeight, const utf8* InTitle)
		:
		Width(InWidth),
		Height(InHeight),
		bShouldClose(false),
		Title(_strdup(InTitle))
	{
		if (MainEditor)
		{
			MainEditor->Destroy();
		}
		else
		{
			MainEditor = this;
		}
	}

	void AMainEditor::AddMenus(HWND InHWND)
	{
		HMENU PackageMenu = CreateMenu();

		// Add Items To PackageMenu
		AppendMenu(PackageMenu, MF_STRING, static_cast<UINT_PTR>(EEditorMenu::PACKAGE_MENU_WINDOWS_32_BIT), "Windows (32-bit)");
		AppendMenu(PackageMenu, MF_STRING, static_cast<UINT_PTR>(EEditorMenu::PACKAGE_MENU_WINDOWS_64_BIT), "Windows (64-bit)");

		HMENU FileMenu = CreateMenu();

		// Add Items To FileMenu
		AppendMenu(FileMenu, MF_STRING, static_cast<UINT_PTR>(EEditorMenu::FILE_MENU_NEW_SCENE), "New Scene...");
		AppendMenu(FileMenu, MF_STRING, static_cast<UINT_PTR>(EEditorMenu::FILE_MENU_OPEN_SCENE), "Open Scene...");
		AppendMenu(FileMenu, MF_STRING, static_cast<UINT_PTR>(EEditorMenu::FILE_MENU_SAVE_CURRENT), "Save Current");
		AppendMenu(FileMenu, MF_STRING, static_cast<UINT_PTR>(EEditorMenu::FILE_MENU_SAVE_CURRENT_AS), "Save Current As...");
		AppendMenu(FileMenu, MF_STRING, static_cast<UINT_PTR>(EEditorMenu::FILE_MENU_SAVE_ALL), "Save All");
		AppendMenu(FileMenu, MF_SEPARATOR, 0, 0);
		AppendMenu(FileMenu, MF_STRING, static_cast<UINT_PTR>(EEditorMenu::FILE_MENU_NEW_PROJECT), "New Project...");
		AppendMenu(FileMenu, MF_STRING, static_cast<UINT_PTR>(EEditorMenu::FILE_MENU_OPEN_PROJECT), "Open Project...");
		AppendMenu(FileMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(PackageMenu), "Package Project");
		AppendMenu(FileMenu, MF_SEPARATOR, 0, 0);
		AppendMenu(FileMenu, MF_STRING, static_cast<UINT_PTR>(EEditorMenu::FILE_MENU_EXIT), "Exit");

		HMENU EditMenu = CreateMenu();

		// Add Items To EditMenu
		AppendMenu(EditMenu, MF_STRING, static_cast<UINT_PTR>(EEditorMenu::EDIT_MENU_UNDO), "Undo");
		AppendMenu(EditMenu, MF_STRING, static_cast<UINT_PTR>(EEditorMenu::EDIT_MENU_REDO), "Redo");
		AppendMenu(EditMenu, MF_SEPARATOR, 0, 0);
		AppendMenu(EditMenu, MF_STRING, static_cast<UINT_PTR>(EEditorMenu::EDIT_MENU_CUT), "Cut");
		AppendMenu(EditMenu, MF_STRING, static_cast<UINT_PTR>(EEditorMenu::EDIT_MENU_COPY), "Copy");
		AppendMenu(EditMenu, MF_STRING, static_cast<UINT_PTR>(EEditorMenu::EDIT_MENU_PASTE), "Paste");
		AppendMenu(EditMenu, MF_STRING, static_cast<UINT_PTR>(EEditorMenu::EDIT_MENU_DUPLICATE), "Duplicate");
		AppendMenu(EditMenu, MF_STRING, static_cast<UINT_PTR>(EEditorMenu::EDIT_MENU_DELETE), "Delete");
		AppendMenu(EditMenu, MF_SEPARATOR, 0, 0);
		AppendMenu(EditMenu, MF_STRING, static_cast<UINT_PTR>(EEditorMenu::EDIT_MENU_PROJECT_SETTINGS), "Project Settings...");

		HMENU WindowMenu = CreateMenu();

		// Add Items To WindowMenu
		// TODO: Add Items

		HMENU HelpMenu = CreateMenu();

		// Add Items To HelpMenu
		AppendMenu(HelpMenu, MF_STRING, static_cast<UINT_PTR>(EEditorMenu::HELP_MENU_ABOUT_EDITOR), "About Avalon Editor...");

		Menu = CreateMenu();

		// Add Items To MainMenu
		AppendMenu(Menu, MF_POPUP, reinterpret_cast<UINT_PTR>(FileMenu), "File");
		AppendMenu(Menu, MF_POPUP, reinterpret_cast<UINT_PTR>(EditMenu), "Edit");
		AppendMenu(Menu, MF_POPUP, reinterpret_cast<UINT_PTR>(WindowMenu), "Window");
		AppendMenu(Menu, MF_POPUP, reinterpret_cast<UINT_PTR>(HelpMenu), "Help");

		SetMenu(InHWND, Menu);
	}

	void AMainEditor::ProcessMenus(WPARAM InWPARAM)
	{
		switch (static_cast<EEditorMenu>(InWPARAM))
		{
		case EEditorMenu::FILE_MENU_EXIT:
			bShouldClose = true;
			break;
		}
	}

	void AMainEditor::Destroy(void)
	{
		DestroyWindow(static_cast<HWND>(Handle));
		delete Title;
	}

	void AMainEditor::Start(void)
	{
		InitializeWindow();
		InitializeWorld();
	}

	void AMainEditor::InitializeWindow(void)
	{
		WNDCLASS WindowClass;
		WindowClass.style = CS_HREDRAW | CS_VREDRAW;
		WindowClass.lpfnWndProc = WinProcedure;
		WindowClass.cbClsExtra = 0;
		WindowClass.cbWndExtra = 0;
		WindowClass.hInstance = nullptr;
		WindowClass.hIcon = LoadIcon(0, IDI_APPLICATION);
		WindowClass.hCursor = LoadCursor(0, IDC_ARROW);
		WindowClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
		WindowClass.lpszClassName = "Avalon Window";
		WindowClass.lpszMenuName = 0;

		if (RegisterClass(&WindowClass) == 0)
		{
			return;
		}

		Handle = CreateWindow(
			WindowClass.lpszClassName,
			Title,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			Width,
			Height,
			nullptr,
			nullptr,
			nullptr,
			nullptr
		);

		if (Handle == nullptr)
		{
			return;
		}

		ShowWindow(Handle, SW_SHOW);
		UpdateWindow(Handle);
	}

	void AMainEditor::InitializeWorld(void)
	{
		World = new AWorld();
		World->Start();

		// Create Test Scene
		AScene* Scene = new AScene;

		// Create Textures
		ATexture2D* GokuTexture1 = new ATexture2D("goku.png");

		// Create Materials
		AMaterial* TestMaterial1 = new AMaterial();
		TestMaterial1->SetDiffuse(GokuTexture1);

		// Create Actors
		AActor* TestActor1 = new AActor(XMFLOAT2(000.0f, 000.0f), TestMaterial1);

		// Add To Scene
		Scene->AddActor(TestActor1);

		// Load Scene
		World->LoadScene(Scene);
	}

	void AMainEditor::PollMessages(void)
	{
		MSG Message = { 0 };

		if (PeekMessage(&Message, nullptr, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
			{
				bShouldClose = true;
			}

			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}

	void AMainEditor::Run(void)
	{
		while (GetShouldClose() == false)
		{
			PollMessages();

			// Editor Loop
			World->Draw();
		}
	}

	LRESULT CALLBACK AMainEditor::WindowProcedure(HWND InHWND, UINT InMSG, WPARAM InWPARAM, LPARAM InLPARAM)
	{
		switch (InMSG)
		{
		case WM_COMMAND:
			ProcessMenus(InWPARAM);
			break;
		case WM_CREATE:
			AddMenus(InHWND);
			break;
		case WM_DESTROY:
			PostQuitMessage(EXIT_SUCCESS);
			return EXIT_SUCCESS;
		}

		return DefWindowProc(InHWND, InMSG, InWPARAM, InLPARAM);
	}

	bool AMainEditor::GetShouldClose(void) const
	{
		return bShouldClose;
	}

	HWND AMainEditor::GetHandle(void) const
	{
		return Handle;
	}

	uint32 AMainEditor::GetWidth(void) const
	{
		return Width;
	}

	uint32 AMainEditor::GetHeight(void) const
	{
		return Height;
	}

	AMainEditor* GetMainEditor(void)
	{
		return MainEditor;
	}
}