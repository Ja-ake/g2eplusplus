#include "Window.h"
#include "windowcomponent.h"

Window::Window(int w, int h, std::string t, bool f) {
	this->add(new WindowComponent(nullptr, w, h, t, f));
}

Window::~Window() {
}

void Window::initialize() {

}
