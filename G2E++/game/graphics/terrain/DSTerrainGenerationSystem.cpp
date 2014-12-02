#include <game/graphics/terrain/DSTerrainGenerationSystem.h>

#include <iostream>
#include <cmath>
#include <random>
#include <time.h>

#include "terraincomponent.h"

using std::cout;
using std::endl;
using g2e::AbstractEntity;

DSTerrainGenerationSystem::DSTerrainGenerationSystem() {
	srand(time(0));
}

DSTerrainGenerationSystem::~DSTerrainGenerationSystem() {
}

void DSTerrainGenerationSystem::initialize(AbstractEntity* entity) {
	TerrainComponent* terrain = (TerrainComponent*) entity->get("TerrainComponent");
	for (int i=0; i<terrain->width; i++) {
		for (int j=0; j<terrain->height; j++) {
			terrain->heightmap[i][j] = (double) ((int) ((i+j)/2));
		}
	}
}
