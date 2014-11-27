#ifndef WINDOWS_WINDOWCOMPONENT_H_
#define WINDOWS_WINDOWCOMPONENT_H_

#include <g2e/core/abstractcomponent.h>
#include <windows.h>

class WindowComponent : public g2e::AbstractComponent {
public:
	WindowComponent(HINSTANCE, int, int, std::string, bool);
	virtual ~WindowComponent();
	virtual std::string getClass() { return "WindowComponent"; }
	virtual void initialize() {}

	HDC hDC;
	HGLRC hRC;
	HWND hWnd;
	HINSTANCE hInstance;

	bool fullscreen;
	int width, height;
	std::string title;
};

#endif /* WINDOWS_WINDOWCOMPONENT_H_ */
