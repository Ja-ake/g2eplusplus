#ifndef WINDOWS_WINDOW_H_
#define WINDOWS_WINDOW_H_

#include <g2e/core/abstractentity.h>
#include <windows.h>

class Window : public g2e::AbstractEntity {
public:
	Window(int w, int h, std::string t, bool f);
	virtual ~Window();
	virtual std::string getClass() { return "Window"; }

	virtual void initialize();
};

#endif /* WINDOWS_WINDOW_H_ */
