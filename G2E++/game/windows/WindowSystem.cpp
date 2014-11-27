#include "windowsystem.h"
#include "window.h"
#include "g2e/core/core.h"
#include <g2e/core/abstractentity.h>
#include <g2e/resource/resourceloaderservice.h>
#include "gl3w.h"
#include <iostream>

using g2e::Core;
using g2e::AbstractEntity;

WindowSystem::WindowSystem() {
}

WindowSystem::~WindowSystem() {
}

void WindowSystem::initialize(AbstractEntity* entity) {
	AbstractEntity* window = dynamic_cast<AbstractEntity*> (entity);
	createWindow((WindowComponent*)window->get("WindowComponent"), 32, false);
}

void WindowSystem::initialize() {

}

void WindowSystem::update(AbstractEntity* entity) {
	SwapBuffers(((WindowComponent*)(dynamic_cast<AbstractEntity*> (entity)
			->get("WindowComponent")))->hDC);
}

void WindowSystem::update() {
	MSG msg;
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			Core::done();
		} else {
			TranslateMessage (&msg);
			DispatchMessage(&msg);
		}
	}
}

BOOL WindowSystem::createWindow(WindowComponent* window, int bits, bool fullscreenflag) {
	GLuint PixelFormat;
	WNDCLASS wc;
	DWORD dwExStyle;
	DWORD dwStyle;
	RECT WindowRect;
	WindowRect.left = (long) 0;
	WindowRect.right = (long) window->width;
	WindowRect.top = (long) 0;
	WindowRect.bottom = (long) window->height;

	window->fullscreen = fullscreenflag;

	window->hInstance = GetModuleHandle(NULL);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC) WindowSystem::WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = window->hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "OpenGL";

	if (!RegisterClass(&wc)) {
		MessageBox(NULL, "Failed to register the window class.", "ERROR",
		MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (window->fullscreen) {
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = window->width;
		dmScreenSettings.dmPelsHeight = window->height;
		dmScreenSettings.dmBitsPerPel = bits;
		dmScreenSettings.dmFields =
		DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings,
		CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {

			if (MessageBox(NULL,
					"The requested fullscreen mode is not supported by\nyour video card. Use windowed mode instead?",
					"Fullscreen", MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
				window->fullscreen = FALSE;
			} else {

				MessageBox(NULL, "Program will now close.", "ERROR",
				MB_OK | MB_ICONSTOP);
				return FALSE;
			}
		}
	}

	if (window->fullscreen) {
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		ShowCursor(FALSE);
	} else {
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);

	if (!(window->hWnd = CreateWindowEx(dwExStyle, "OpenGL", window->title.c_str(), dwStyle |
	WS_CLIPSIBLINGS |
	WS_CLIPCHILDREN, 0, 0, WindowRect.right - WindowRect.left,
			WindowRect.bottom - WindowRect.top,
			NULL,
			NULL, window->hInstance,
			NULL))) {
		killWindow(window);
		MessageBox(NULL, "Window Creation Error.", "ERROR",
		MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	static PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR), 1,
	PFD_DRAW_TO_WINDOW |
	PFD_SUPPORT_OPENGL |
	PFD_DOUBLEBUFFER,
	PFD_TYPE_RGBA, bits, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0,
	PFD_MAIN_PLANE, 0, 0, 0, 0 };

	if (!(window->hDC = GetDC(window->hWnd))) {
		killWindow(window);
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR",
		MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!(PixelFormat = ChoosePixelFormat(window->hDC, &pfd))) {
		killWindow(window);
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR",
		MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!SetPixelFormat(window->hDC, PixelFormat, &pfd)) {
		killWindow(window);
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR",
		MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!(window->hRC = wglCreateContext(window->hDC))) {
		killWindow(window);
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR",
		MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!wglMakeCurrent(window->hDC, window->hRC)) {
		killWindow(window);
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR",
		MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (gl3wInit()) {
		std::cout << "Error initalizing gl3w" << std::endl;
		return 1;
	}

	ShowWindow(window->hWnd, SW_SHOW);
	SetForegroundWindow(window->hWnd);
	SetFocus(window->hWnd);
	resizeWindow(window, window->width, window->height);

	if (!initializeGL()) {
		killWindow(window);
		MessageBox(NULL, "Initialization Failed.", "ERROR",
		MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;
}

void WindowSystem::killWindow(WindowComponent* window) {
	if (window->fullscreen) {
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}

	if (window->hRC) {
		if (!wglMakeCurrent(NULL, NULL)) {
			MessageBox(NULL, "Release of DC and RC failed.", "SHUTDOWN ERROR",
			MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(window->hRC)) {
			MessageBox(NULL, "Release rendering context failed.",
					"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		window->hRC = NULL;
	}

	if (window->hDC && !ReleaseDC(window->hWnd, window->hDC)) {
		MessageBox(NULL, "Release device context failed.", "SHUTDOWN ERROR",
		MB_OK | MB_ICONINFORMATION);
		window->hDC = NULL;
	}

	if (window->hWnd && !DestroyWindow(window->hWnd)) {
		MessageBox(NULL, "Could not release HWND.", "SHUTDOWN ERROR",
		MB_OK | MB_ICONINFORMATION);
		window->hWnd = NULL;
	}

	if (!UnregisterClass("OpenGL", window->hInstance)) {
		MessageBox(NULL, "Could not unregister class.", "SHUTDOWN ERROR",
		MB_OK | MB_ICONINFORMATION);
		window->hInstance = NULL;
	}
}

void WindowSystem::resizeWindow(WindowComponent* window, int w, int h) {
	if (h == 0) {
		h = 1;
	}

	window->width = w;
	window->height = h;

	glViewport(0, 0, w, h);
}

BOOL WindowSystem::initializeGL() {
	g2e::Core::service().add(nullptr);
	return TRUE;
}

LRESULT CALLBACK WindowSystem::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_ACTIVATE: {
		if (!HIWORD(wParam)) {
			// active
		} else {
			// not active
		}

		return 0;
	}

	case WM_SYSCOMMAND: {
		switch (wParam) {
		case SC_SCREENSAVE:
		case SC_MONITORPOWER:
			return 0;
		}
		break;
	}

	case WM_CLOSE: {
		PostQuitMessage(0);
		return 0;
	}

	case WM_KEYDOWN: {
		std::cout << (char)HIWORD(wParam) << std::endl;
		return 0;
	}

	case WM_KEYUP: {
		std::cout << (char)HIWORD(wParam) << std::endl;
		return 0;
	}

	case WM_SIZE: {
		// fire size event at window
		return 0;
	}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
