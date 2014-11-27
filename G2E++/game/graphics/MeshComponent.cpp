#include "MeshComponent.h"

MeshComponent::MeshComponent(int s, double* v) : size(s), vertices(v) {
}

MeshComponent::~MeshComponent() {
	delete[] vertices;
}

