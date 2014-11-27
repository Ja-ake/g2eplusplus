#ifndef WINDOWS_WINDOWSYSTEM_H_
#define WINDOWS_WINDOWSYSTEM_H_

#include <g2e/core/abstractsystem.h>
#include "windowcomponent.h"

#include <windows.h>

class WindowSystem : public g2e::AbstractSystem {
public:
	WindowSystem();
	virtual ~WindowSystem();
	virtual std::string getClass() { return "WindowSystem"; }

	virtual void initialize(g2e::AbstractEntity*);
	virtual void initialize();
	virtual void update(g2e::AbstractEntity*);
	virtual void update();

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

private:
	BOOL createWindow(WindowComponent*, int, bool);
	void killWindow(WindowComponent*);
	BOOL initializeGL();
	void resizeWindow(WindowComponent*, int, int);
};

#endif /* WINDOWS_WINDOWSYSTEM_H_ */
