#include "TerrainRenderSystem.h"
#include "terraincomponent.h"
#include <g2e/core/core.h>
#include <glm/glm.hpp>
#include <iostream>

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

	terrain->buffer = opengl->upload(v, 6*3, GL_ARRAY_BUFFER);

	const char* terrainvert = GLSL(
		layout(location = 0)
		in vec3 position;
		uniform mat4 model;
		uniform mat4 viewproj;

		void main() {
			gl_Position = viewproj*model*vec4(position, 1.0f);
		}
	);

	const char* terrainfrag = GLSL(
		out vec4 outColor;

		void main() {
			outColor = vec4(1.0, 1.0, 1.0, 1.0);
		}
	);
	terrain->program = opengl->createProgramSrc(terrainvert, terrainfrag);
}

void TerrainRenderSystem::update(g2e::AbstractEntity* entity) {
	TerrainComponent* terrain = (TerrainComponent*) entity->get("TerrainComponent");
	OpenGLService* opengl = (OpenGLService*) Core::service().get("OpenGLService");

	glUseProgram(terrain->program);

	glm::mat4 vp = opengl->getProjection() * opengl->getView();
	GLuint viewproj = glGetUniformLocation(terrain->program, "viewproj");
	glUniformMatrix4fv(viewproj, 1, GL_FALSE, &vp[0][0]);

	GLint position = glGetAttribLocation(terrain->program, "position");
	GLint model = glGetUniformLocation(terrain->program, "model");

	glBindVertexArray(terrain->buffer.vao);
	glBindBuffer(GL_ARRAY_BUFFER, terrain->buffer.vbo);

	glEnableVertexAttribArray(position);
	glVertexAttribPointer(position, 3, GL_DOUBLE, GL_FALSE, 0, 0);

	for (int i=0; i<terrain->width; i++) {
		for (int j=0; j<terrain->height; j++) {
			glm::mat4 modelMatrix = glm::translate(glm::mat4(),
						glm::vec3(i-terrain->width/2, terrain->heightmap[i][j], j-terrain->height/2));
			glUniformMatrix4fv(model, 1, GL_FALSE, &modelMatrix[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, 6*3);
		}
	}

	glDisableVertexAttribArray(position);
	glUseProgram(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
