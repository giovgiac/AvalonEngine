/**
 * Window.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "Window.h"

#include <Windows.h>

LRESULT CALLBACK WindowProcedure(HWND InHWND, UINT InMSG, WPARAM InWPARAM, LPARAM InLPARAM)
{
	switch (InMSG)
	{
	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);
		return EXIT_SUCCESS;
	}

	return DefWindowProc(InHWND, InMSG, InWPARAM, InLPARAM);
}

namespace Avalon 
{
	AWindow::AWindow(const uint32 InWidth, const uint32 InHeight, const utf8* InTitle, const bool InFullscreen)
		: 
		Width(InWidth),
		Height(InHeight),
		bFullscreen(InFullscreen),
		bShouldClose(false),
		Title(_strdup(InTitle)) 
	{
		
	}

	void AWindow::Destroy(void)
	{
		DestroyWindow(static_cast<HWND>(Handle));
		delete Title;
	}

	EWindowCreationError AWindow::Start(void)
	{
		WNDCLASS WindowClass;
		WindowClass.style = CS_HREDRAW | CS_VREDRAW;
		WindowClass.lpfnWndProc = WindowProcedure;
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
			// TODO: Use Avalon Debug System To Log Out Error Message
			return EWindowCreationError::FAILED_TO_REGISTER_CLASS;
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
			// TODO: Use Avalon Debug System To Log Out Error Message
			return EWindowCreationError::FAILED_TO_CREATE_WINDOW;
		}

		ShowWindow(static_cast<HWND>(Handle), SW_SHOW);
		UpdateWindow(static_cast<HWND>(Handle));

		return EWindowCreationError::SUCCESS;
	}

	void AWindow::PollMessages(void)
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

	bool AWindow::GetShouldClose(void) const
	{
		return bShouldClose;
	}

	uint32 AWindow::GetWidth(void) const
	{
		return Width;
	}

	uint32 AWindow::GetHeight(void) const
	{
		return Height;
	}
}