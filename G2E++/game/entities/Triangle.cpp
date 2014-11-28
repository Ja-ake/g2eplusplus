#include "Triangle.h"
#include "../graphics/meshcomponent.h"
#include <random>
#include <iostream>

Triangle::Triangle() {
}

Triangle::~Triangle() {
}

void Triangle::initialize() {
	double* vertices = new double[9];
	vertices[0] = -1.0f; vertices[1] = 0.0f; vertices[2] = -0.0f;
	vertices[3] = 1.0f; vertices[4] = 0.0f; vertices[5] = -0.0f;
	vertices[6] = 0.0f; vertices[7] = 1.0f*((double)(rand()%2)); vertices[8] = -0.0f;

	this->add(new MeshComponent(9, &vertices[0]));
}
