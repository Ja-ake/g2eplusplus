#include <gl3w.h>
#include <glcorearb.h>

#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>

#include "../g2e/core/Core.h"
#include "../g2e/gl/Mesh.h"
#include "../g2e/math/Vector2.h"
#include "../g2e/math/Vector3.h"

#include "windows/windowsystem.h"
#include "windows/window.h"
#include "entities/triangle.h"
#include "graphics/meshrendersystem.h"
#include <g2e/resource/resourceloaderservice.h>

using g2e::Core;
using g2e::io::ResourceLoaderService;
using std::cout;
using std::endl;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		LPSTR lpCmdLine, int nCmdShow) {
	rand();

	Core::addDefaultServices();

	Core::add(new WindowSystem());
	Core::get("WindowSystem")->add(new Window(nullptr, 1200, 900, "Game", false));

	Core::add(new MeshRenderSystem());
	Core::get("MeshRenderSystem")->add(new Triangle());
	Core::get("MeshRenderSystem")->add(new Triangle());

	Core::run();
	return 0;
}
