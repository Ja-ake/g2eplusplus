#include <game/graphics/terrain/Terrain.h>
#include "terraincomponent.h"

#include <random>
#include <iostream>

using std::cout;
using std::endl;

Terrain::Terrain() {
}

Terrain::~Terrain() {
}

void Terrain::initialize() {
	TerrainComponent* terrain;
	this->add(terrain = new TerrainComponent(16, 16));

	for (int i=0; i<terrain->width; i++) for (int j=0; j<terrain->height; j++) terrain->heightmap[i][j]=(rand()%20)-10;
}
