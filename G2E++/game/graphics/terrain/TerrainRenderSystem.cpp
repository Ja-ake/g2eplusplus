#include "TerrainRenderSystem.h"
#include "terraincomponent.h"
#include <g2e/core/core.h>

using g2e::gl::OpenGLService;
using g2e::Core;

TerrainRenderSystem::TerrainRenderSystem() {
}

TerrainRenderSystem::~TerrainRenderSystem() {
}

void TerrainRenderSystem::initialize() {

}

void TerrainRenderSystem::update() {

}

void TerrainRenderSystem::initialize(g2e::AbstractEntity* entity) {
	TerrainComponent* terrain = (TerrainComponent*) entity->get("TerrainComponent");
	OpenGLService* opengl = (OpenGLService*) Core::service().get("OpenGLService");

	double* v = new double[6*3]; {
		v[0] =  0.0f, v[1] =  0.0f, v[2] =  0.0f;
		v[3] =  1.0f, v[4] =  0.0f, v[5] =  0.0f;
		v[6] =  0.0f, v[7] =  0.0f, v[8] =  1.0f;

		v[9] =  0.0f, v[10] = 0.0f, v[11] = 1.0f;
		v[12] = 1.0f, v[13] = 0.0f, v[14] = 1.0f;
		v[15] = 1.0f, v[16] = 0.0f, v[17] = 0.0f;
	}

	opengl->upload(v, 18, GL_ARRAY_BUFFER);

	const char* terrainvert = GLSL(
		in vec3 position;

		void main() {
			gl_Position = vec4(pos, 1.0f);
		}
	);

	const char* terrainfrag = GLSL(
		out vec4 outColor;

		void main() {
			outColor = vec4(1.0, 0.0, 0.0, 1.0);
		}
	);

	opengl->createProgramSrc(terrainvert, terrainfrag);
}

void TerrainRenderSystem::update(g2e::AbstractEntity* entity) {
	TerrainComponent* terrain = (TerrainComponent*) entity->get("TerrainComponent");
	OpenGLService opengl = (OpenGLService*) Core::service().get("OpenGLService");

}
