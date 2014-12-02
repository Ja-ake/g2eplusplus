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
#include "graphics/terrain/terrainrendersystem.h"
#include "graphics/terrain/dsterraingenerationsystem.h"
#include "graphics/terrain/terrain.h"
#include "graphics/camera/noclipcamerasystem.h"
#include "graphics/camera/camera.h"
#include "physics/movement/velocitysystem.h"

#include <g2e/resource/resourceloaderservice.h>

using g2e::Core;
using g2e::io::ResourceLoaderService;
using std::cout;
using std::endl;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		LPSTR lpCmdLine, int nCmdShow) {
	rand();

	Core::addDefaultServices();

	Core::add(new VelocitySystem());

	Core::add(new WindowSystem());
	Core::get("WindowSystem")->add(new Window(1200, 900, "Game", true));

	Camera* camera = new Camera();
	Core::add(new NoClipCameraSystem());
	Core::get("NoClipCameraSystem")->add(camera);
	Core::get("VelocitySystem")->add(camera);

	Terrain* terrain = new Terrain();
	Core::add(new TerrainRenderSystem());
	//Core::add(new DSTerrainGenerationSystem());
	//Core::get("DSTerrainGenerationSystem")->add(terrain);
	Core::get("TerrainRenderSystem")->add(terrain);

	SetCursorPos(600, 450);

	Core::run();
	return 0;
}
