#include "TerrainComponent.h"

#include <iostream>

using g2e::math::Color;
using std::cout;
using std::endl;

TerrainComponent::TerrainComponent(int w, int h) : width(w), height(h) {
	heightmap = new double*[width];
	colormap = new Color*[width];
	for (int i=0; i<width; i++) heightmap[i] = new double[height];
	for (int i=0; i<width; i++) colormap[i] = new Color[height];
	for (int i=0; i<width; i++) for (int j=0; j<height; j++)
		{ heightmap[i][j] = 0.0f; colormap[i][j] = Color(0.0f, 1.0f, 0.0f); }
}

TerrainComponent::~TerrainComponent() {
	for (int i=0; i<width; i++) delete heightmap[i];
	for (int i=0; i<width; i++) delete colormap[i];
	delete[] heightmap;
	delete[] colormap;
}

