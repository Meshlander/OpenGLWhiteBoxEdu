/* ======================================================
SFile: WinMain.cpp
SDate: 2021.10.03.
SRevision: S
SCreator: Gergely Zara
SNotice: S
======================================================*/

#include "WinMain.h"
#include "Vectors.h"
#include "SystemIO.h"
#include "SoftAccelDisplay.h"
#include "OpenGL.h"

#include "SoftAccelDisplay.cpp"
#include "OpenGL.cpp"

int Running = 1;

LRESULT CALLBACK //This is where messages received from the window are processed.
WindowProc
(
	HWND window,
	UINT message,
	WPARAM w_param,
	LPARAM l_param
)
{
	LRESULT result;
	switch (message)
	{
		case WM_CLOSE:
		{
			DestroyWindow(window);
			//wglDeleteContext(WindowProperties[0].OpenGLHandle);
			Running = 0;
		} break;

		case WM_KEYUP:
		{

		} break;

		case WM_KEYDOWN:
		{

		} break;

	}

	result = DefWindowProc
	(
		window,
		message,
		w_param,
		l_param
	);

	return result;
}

int WINAPI wWinMain //The Windows entry point cannot be embedded in a class
(
	HINSTANCE instance,
	HINSTANCE prev_instance,
	PWSTR cmd_line,
	int cmd_show
)
{
	AllocConsole();
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, 640, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	freopen("CONOUT$", "w", stdout);
	printf("Console was successfully opened."); printf("\n");

	WNDCLASS WindowClass = {};
	WindowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpfnWndProc = WindowProc;
	WindowClass.hInstance = instance;
	WindowClass.lpszClassName = (LPCSTR)"WindowClass";
	WindowClass.hCursor = LoadCursor(0, IDC_CROSS);
	RegisterClass(&WindowClass);

	HWND window = CreateWindowEx
	(
		0,
		WindowClass.lpszClassName,
		(LPCSTR)"Game",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0,//StartX
		0,//StartY
		640,//EndX
		480,//EndY
		0,
		0,
		instance,
		0
	);

	HDC hdc = GetDC(window);
	printf("Window was successfully created."); printf("\n");

//START_FUNCTIONS

	InitOpenGL(window);
	//Buffers need to be swapped once by the software, for OpenGL to work.
	//The buffer does not need to be initialized though.
	SwapBuffers(hdc);

	//UPDATE_LOOP

	while (Running)
	{
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		//UPDATE_FUNCTIONS
		GLDraw();
	}

	FreeConsole();
	return 0;
}