#include "Window.h"
#include "windowcomponent.h"

Window::Window(HINSTANCE hi, int w, int h, std::string t, bool f) {
	this->add(new WindowComponent(hi, w, h, t, f));
}

Window::~Window() {
}

void Window::initialize() {

}
