#include "Triangle.h"
#include "../graphics/meshcomponent.h"

Triangle::Triangle() {
}

Triangle::~Triangle() {
}

void Triangle::initialize() {
	double vertices[] = {
			-1.0f, 0.0f, -1.0f,
			1.0f, 0.0f, -1.0f,
			0.0f, 1.0f, -1.0f
	};

	this->add(new MeshComponent(9, &vertices[0]));
}
