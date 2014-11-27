#include "main.h"

using std::cout;
using std::endl;
using g2e::math::Vector2;
using g2e::math::Vector3;
using g2e::gl::Mesh;

HDC hDC = NULL;
HGLRC hRC = NULL;
HWND hWnd = NULL;
HINSTANCE hInstance;

bool keys[256];
bool active = TRUE;
bool fullscreen = TRUE;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

GLvoid resizeWindow(GLsizei width, GLsizei height) {
	if (height == 0) {
		height = 1;
	}

	glViewport(0, 0, width, height);
}

int initialize() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
//	glClearDepth(10.0f);
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_COLOR);
	glDepthFunc(GL_LEQUAL);
//	glOrtho(-1, 1, -1, 1, -100, 100);
	return TRUE;
}

int draw() {
	glClear(GL_COLOR_BUFFER_BIT/* | GL_DEPTH_BUFFER_BIT*/);
	glClearColor(1.0, 1.0, 0.0, 1.0);
	return TRUE;
}

GLvoid killWindow() {
	if (fullscreen) {
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}

	if (hRC) {
		if (!wglMakeCurrent(NULL, NULL)) {
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR",
			MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC)) {
			MessageBox(NULL, "Release Rendering Context Failed.",
					"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;
	}

	if (hDC && !ReleaseDC(hWnd, hDC)) {
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR",
		MB_OK | MB_ICONINFORMATION);
		hDC = NULL;
	}

	if (hWnd && !DestroyWindow(hWnd)) {
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR",
		MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;
	}

	if (!UnregisterClass("OpenGL", hInstance)) {
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR",
		MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL createWindow(char* title, int width, int height, int bits,
		bool fullscreenflag) {
	GLuint PixelFormat;
	WNDCLASS wc;
	DWORD dwExStyle;
	DWORD dwStyle;
	RECT WindowRect;
	WindowRect.left = (long) 0;
	WindowRect.right = (long) width;
	WindowRect.top = (long) 0;
	WindowRect.bottom = (long) height;

	fullscreen = fullscreenflag;

	hInstance = GetModuleHandle(NULL);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
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

	if (fullscreen) {
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = width;
		dmScreenSettings.dmPelsHeight = height;
		dmScreenSettings.dmBitsPerPel = bits;
		dmScreenSettings.dmFields =
		DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings,
		CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {

			if (MessageBox(NULL,
					"The requested fullscreen mode is not supported by\nyour video card. Use windowed mode instead?",
					"Fullscreen", MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
				fullscreen = FALSE;
			} else {

				MessageBox(NULL, "Program will now close.", "ERROR",
				MB_OK | MB_ICONSTOP);
				return FALSE;
			}
		}
	}

	if (fullscreen) {
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		ShowCursor(FALSE);
	} else {
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);

	if (!(hWnd = CreateWindowEx(dwExStyle, "OpenGL", title, dwStyle |
	WS_CLIPSIBLINGS |
	WS_CLIPCHILDREN, 0, 0, WindowRect.right - WindowRect.left,
			WindowRect.bottom - WindowRect.top,
			NULL,
			NULL, hInstance,
			NULL))) {
		killWindow();
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

	if (!(hDC = GetDC(hWnd))) {
		killWindow();
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR",
		MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd))) {
		killWindow();
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR",
		MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd)) {
		killWindow();
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR",
		MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!(hRC = wglCreateContext(hDC))) {
		killWindow();
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR",
		MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!wglMakeCurrent(hDC, hRC)) {
		killWindow();
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR",
		MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (gl3wInit()) {
		std::cout << "Error initalizing gl3w" << std::endl;
		return 1;
	}

	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	resizeWindow(width, height);

	if (!initialize()) {
		killWindow();
		MessageBox(NULL, "Initialization Failed.", "ERROR",
		MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_ACTIVATE: {
		if (!HIWORD(wParam)) {
			active = TRUE;
		} else {
			active = FALSE;
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
		keys[wParam] = TRUE;
		return 0;
	}

	case WM_KEYUP: {
		keys[wParam] = FALSE;
		return 0;
	}

	case WM_SIZE: {
		resizeWindow(LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//




GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile) {
	GLuint shader = glCreateShader(eShaderType);
	const char *strFileData = strShaderFile.c_str();
	glShaderSource(shader, 1, &strFileData, NULL);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch (eShaderType) {
		case GL_VERTEX_SHADER:
			strShaderType = "vertex";
			break;
		case GL_GEOMETRY_SHADER:
			strShaderType = "geometry";
			break;
		case GL_FRAGMENT_SHADER:
			strShaderType = "fragment";
			break;
		}

		std::cerr << "Error creating shader" << std::endl;
		delete[] strInfoLog;
	}

	return shader;
}

GLuint createProgram(const std::vector<GLuint> &shaderList) {
	GLuint program = glCreateProgram();

	for (size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glAttachShader(program, shaderList[iLoop]);

	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		delete[] strInfoLog;

		std::cerr << "Error creating program" << std::endl;
	}

	for (size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glDetachShader(program, shaderList[iLoop]);

	return program;
}

GLuint initializeProgram() {
	std::vector<GLuint> shaderList;

	shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER,
			"#version 330\r\n out vec4 outputColor;void main(){outputColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);}"));
	shaderList.push_back(CreateShader(GL_VERTEX_SHADER,
			"#version 330\r\n layout(location = 0) in vec4 position;void main(){gl_Position = position;}"));


	GLuint ret = createProgram(shaderList);

	std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);

	return ret;
}




///

//class I {
//public:
//	virtual ~I() {}
//	virtual void getI() { int kk = 4; }
//	virtual long long getK() { return kk; }
//private:
//	long long kk = 400;
//};
//
//class J : public I {
//public:
//	virtual ~J() {}
//	virtual void getI() { int kk=0; }
//};
//
//class K : public J {
//public:
//	virtual ~K() {}
//	virtual void getI() { int kk=0; }
//};

int WINAPI WinaMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		LPSTR lpCmdLine, int nCmdShow) {
	try {
	MSG msg;
	BOOL done = FALSE;
	const char* wndtitle = std::string("G2E++").c_str();
	fullscreen = false;

	if (!createWindow((char*) wndtitle, 640, 480, 16, fullscreen)) {
		std::cout << "Error creating window" << std::endl;
		return 1;
	}

//	int* iptr = (int*)new I();
//	int* jptr = (int*)new J();
//	int* kptr = (int*)new K();
//
//	cout << sizeof(*iptr) << " " << sizeof(*jptr) << std::endl;
//	cout << iptr[0] << " " << iptr[1] << std::endl;
//	cout << jptr[0] << " " << jptr[1] << std::endl;
//	cout << kptr[0] << " " << kptr[1] <<std::endl;

	Mesh mesh = Mesh(36);
//	mesh.vertex(1.0, 0.0,   -1.0f);
//	mesh.vertex(0.0, 1.0,   -0.0f);
//	mesh.vertex(-1.0, -1.0, -0.9f);
//	mesh.vertex(-100.4, -200.03, -50);
//	mesh.vertex(2100.2, 0.0, 10);
//	mesh.vertex(-240.2, -200, -10);

	    mesh.vertex(-0.9f,-0.9f,-1.1f);
	    mesh.vertex(-0.9f,-0.9f, 1.1f);
	    mesh.vertex(-0.9f, 0.9f, 1.1f);
	    mesh.vertex(0.9f, 0.9f, -1.1f);
	    mesh.vertex(-0.9f,-0.9f,-1.1f);
	    mesh.vertex(-0.9f, 0.9f,-1.1f);
	    mesh.vertex(0.9f,-0.9f,  1.1f);
	    mesh.vertex(-0.9f,-0.9f,-1.1f);
	    mesh.vertex(0.9f,-0.9f, -1.1f);
	    mesh.vertex(0.9f, 0.9f, -1.1f);
	    mesh.vertex(0.9f,-0.9f, -1.1f);
	    mesh.vertex(-0.9f,-0.9f,-1.1f);
	    mesh.vertex(-0.9f,-0.9f,-1.1f);
	    mesh.vertex(-0.9f, 0.9f, 1.1f);
	    mesh.vertex(-0.9f, 0.9f,-1.1f);
	    mesh.vertex(0.9f,-0.9f,  1.1f);
	    mesh.vertex(-0.9f,-0.9f, 1.1f);
	    mesh.vertex(-0.9f,-0.9f,-1.1f);
	    mesh.vertex(-0.9f, 0.9f, 1.1f);
	    mesh.vertex(-0.9f,-0.9f, 1.1f);
	    mesh.vertex(0.9f,-0.9f,  1.1f);
	    mesh.vertex(0.9f, 0.9f,  1.1f);
	    mesh.vertex(0.9f,-0.9f, -1.1f);
	    mesh.vertex(0.9f, 0.9f, -1.1f);
	    mesh.vertex(0.9f,-0.9f, -1.1f);
	    mesh.vertex(0.9f, 0.9f,  1.1f);
	    mesh.vertex(0.9f,-0.9f,  1.1f);
	    mesh.vertex(0.9f, 0.9f,  1.1f);
	    mesh.vertex(0.9f, 0.9f, -1.1f);
	    mesh.vertex(-0.9f, 0.9f,-1.1f);
	    mesh.vertex(0.9f, 0.9f,  1.1f);
	    mesh.vertex(-0.9f, 0.9f,-1.1f);
	    mesh.vertex(-0.9f, 0.9f, 1.1f);
	    mesh.vertex(0.9f, 0.9f,  1.1f);
	    mesh.vertex(-0.9f, 0.9f, 1.1f);
	    mesh.vertex(0.9f,-0.9f,  1.1f);
//	};

	mesh.upload();

//	glGenBuffers(1, &vbuffer);
//
//	glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
//	glBufferData(GL_ARRAY_BUFFER, (sizeof(float)) * size, vertices,
//	GL_STATIC_DRAW);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	GLuint program = initializeProgram();
	double tick = 0, old = 0;
	while (!done) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				done = TRUE;
			} else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		} else {

			if (active) {
				if (keys[VK_ESCAPE]) {
					done = TRUE;
				} else {
					draw();
					mesh.render();
					tick = (double)GetTickCount();
//					cout << (1.0f/((tick-old)/1000.0f)) << endl;
					old = tick;

					SwapBuffers(hDC);
				}
			}

			if (keys[VK_F1]) {
				keys[VK_F1] = FALSE;
				killWindow();
				fullscreen = !fullscreen;

				if (!createWindow((char*) wndtitle, 640, 480, 16, fullscreen)) {
					return 0;
				}
			}
		}
	}

	killWindow();
	return (msg.wParam);

	} catch (std::runtime_error& error) {
		std::cerr << error.what() << endl;
		return 1;
	}
}
