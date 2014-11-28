#include "MeshRenderSystem.h"
#include "meshcomponent.h"

#include <glcorearb.h>
#include <iostream>

#include <g2e/gl/openglservice.h>
#include <g2e/core/core.h>

using g2e::Core;
using g2e::gl::OpenGLService;

MeshRenderSystem::MeshRenderSystem() {
}

MeshRenderSystem::~MeshRenderSystem() {
}

void MeshRenderSystem::initialize(g2e::AbstractEntity* entity) {
	MeshComponent* mesh = (MeshComponent*)entity->get("MeshComponent");
	OpenGLService* opengl = (OpenGLService*)Core::service().get("OpenGLService");

	mesh->buffers = opengl->upload(mesh->vertices, mesh->size, GL_ARRAY_BUFFER);
	mesh->program = opengl->createProgram("resources/shaders/general.vs", "resources/shaders/general.fs");
}

void MeshRenderSystem::initialize() {

}

void MeshRenderSystem::update(g2e::AbstractEntity* entity) {
	MeshComponent* mesh = (MeshComponent*)entity->get("MeshComponent");
	OpenGLService* opengl = (OpenGLService*)Core::service().get("OpenGLService");

	opengl->useProgram(mesh->program);
	opengl->draw(mesh->buffers);
	opengl->unuseProgram();
}

void MeshRenderSystem::update() {

}
