/**
 * MainEditor.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "MainEditor.h"

#include <Actors/Actor.h>

#include <Core/Timer.h>
#include <Core/Window.h>
#include <Core/World.h>

#include <Graphics/Material.h>
#include <Graphics/Scene.h>
#include <Graphics/Texture.h>

#include <Editor/Controls/Textbox.h>
#include <Editor/Controls/Viewport.h>

static Avalon::UMainEditor* MainEditor = nullptr;

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
	UMainEditor::UMainEditor(const float InWidth, const float InHeight, const utf8* InTitle)
		:
		bShouldClose(false),
		bResizing(false),
		Title(_strdup(InTitle))
	{
		Width = InWidth;
		Height = InHeight;

		if (MainEditor)
		{
			MainEditor->Destroy();
		}
		else
		{
			MainEditor = this;
		}
	}

	void UMainEditor::AddControls(HWND InHWND)
	{
		//Viewport = CreateWindow(WC_DIALOG, "Viewport", WS_BORDER | WS_VISIBLE | WS_CHILD, 320, 96, ViewportWidth, ViewportHeight, InHWND, 0, 0, 0);
		//CreateWindow(WC_STATIC, "Enter Text Here: ", WS_VISIBLE | WS_CHILD | SS_CENTER, 200, 25, 100, 50, InHWND, 0, 0, 0);

		Viewport = new UViewport(this, 0.5f, 0.5f, 640.0f, 480.0f, EAnchorPoint::CENTER);
		Viewport->ConstructControl(InHWND);
		Children.push_back(Viewport);

		UTextbox* Textbox = new UTextbox(this, 0.0f, 0.0f, 100.0f, 20.0f, EAnchorPoint::TOP_LEFT);
		Textbox->ConstructControl(InHWND);
		Children.push_back(Textbox);
	}

	void UMainEditor::AddMenus(HWND InHWND)
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

	void UMainEditor::ProcessMenus(WPARAM InWPARAM)
	{
		AScene* NewScene = nullptr;
		ATexture2D* GokuTexture1 = nullptr;
		AMaterial* TestMaterial1 = nullptr;
		AActor* TestActor1 = nullptr;

		switch (static_cast<EEditorMenu>(InWPARAM))
		{
		case EEditorMenu::FILE_MENU_NEW_SCENE:
			// Create New Scene
			NewScene = new AScene;
			World->LoadScene(NewScene);
			
			break;
		case EEditorMenu::FILE_MENU_OPEN_SCENE:
			// Create Test Scene
			NewScene = new AScene;

			// Create Textures
			GokuTexture1 = new ATexture2D("goku.png");

			// Create Materials
			TestMaterial1 = new AMaterial();
			TestMaterial1->SetDiffuse(GokuTexture1);

			// Create Actors
			TestActor1 = new AActor(XMFLOAT2(000.0f, 000.0f), TestMaterial1);

			// Add To Scene
			NewScene->AddActor(TestActor1);

			// Load Scene
			World->LoadScene(NewScene);
			break;
		case EEditorMenu::FILE_MENU_EXIT:
			bShouldClose = true;
			break;
		}
	}

	void UMainEditor::Destroy(void)
	{
		//DestroyWindow(static_cast<HWND>(Handle));
		DestroyControl();
		delete Title;
	}

	void UMainEditor::Start(void)
	{
		ConstructControl(nullptr);
	}

	void UMainEditor::ConstructControl(HWND InParentHandle)
	{
		InitializeTimer();
		InitializeWindow();
		InitializeWorld();
	}

	void UMainEditor::InitializeWindow(void)
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
			"Avalon Window",
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

	void UMainEditor::InitializeWorld(void)
	{
		World = new AWorld();
		World->Start();
	}

	void UMainEditor::InitializeTimer(void)
	{
		Timer = new ATimer();
		Timer->Start();
	}

	void UMainEditor::PollMessages(void)
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

	void UMainEditor::Run(void)
	{
		Timer->Reset();

		// Editor Loop
		while (GetShouldClose() == false)
		{
			PollMessages();
			Timer->Tick();
			World->Draw();
		}
	}

	void UMainEditor::ResizeControls(void)
	{
		for (UControl* Control : Children)
		{
			Control->ResizeControl();
		}

		World->Resize();
	}

	LRESULT CALLBACK UMainEditor::WindowProcedure(HWND InHWND, UINT InMSG, WPARAM InWPARAM, LPARAM InLPARAM)
	{
		switch (InMSG)
		{
		case WM_ACTIVATE:
			if (LOWORD(InWPARAM) == WA_INACTIVE)
			{
				Timer->Stop();
			}
			else
			{
				Timer->Start();
			}

			return EXIT_SUCCESS;
		case WM_COMMAND:
			ProcessMenus(InWPARAM);
			return EXIT_SUCCESS;
		case WM_CREATE:
			AddMenus(InHWND);
			AddControls(InHWND);
			return EXIT_SUCCESS;
		case WM_DESTROY:
			PostQuitMessage(EXIT_SUCCESS);
			return EXIT_SUCCESS;
		case WM_SIZE:
			Width = LOWORD(InLPARAM);
			Height = HIWORD(InLPARAM);

			if (World)
			{
				if (InWPARAM == SIZE_MAXIMIZED)
				{
					ResizeControls();
				}
				else if (InWPARAM == SIZE_RESTORED)
				{
					if (bResizing == false)
					{
						ResizeControls();
					}
				}
			}

			return EXIT_SUCCESS;
		case WM_ENTERSIZEMOVE:
			bResizing = true;

			Timer->Stop();
			return EXIT_SUCCESS;
		case WM_EXITSIZEMOVE:
			bResizing = false;

			Timer->Start();
			ResizeControls();
			return EXIT_SUCCESS;
		}

		return DefWindowProc(InHWND, InMSG, InWPARAM, InLPARAM);
	}

	bool UMainEditor::GetShouldClose(void) const
	{
		return bShouldClose;
	}

	UViewport* UMainEditor::GetViewport(void) const
	{
		return Viewport;
	}

	UMainEditor* GetMainEditor(void)
	{
		return MainEditor;
	}
}
