#include "WindowComponent.h"

WindowComponent::WindowComponent(HINSTANCE hi, int w, int h, std::string t, bool f)
: hInstance(hi), width(w), height(h), title(t), fullscreen(f) {
	hDC = 0;
	hRC = 0;
	hWnd = 0;
}

WindowComponent::~WindowComponent() {
}

