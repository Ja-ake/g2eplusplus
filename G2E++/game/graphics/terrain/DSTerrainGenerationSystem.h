#ifndef GRAPHICS_TERRAIN_DSTERRAINGENERATIONSYSTEM_H_
#define GRAPHICS_TERRAIN_DSTERRAINGENERATIONSYSTEM_H_

#include <g2e/core/abstractsystem.h>

class DSTerrainGenerationSystem : public g2e::AbstractSystem {
public:
	CLASSNAME(DSTerrainGenerationSystem)

	DSTerrainGenerationSystem();
	virtual ~DSTerrainGenerationSystem();

	virtual void initialize(g2e::AbstractEntity*);
	virtual void initialize() {}
	virtual void update(g2e::AbstractEntity*) {}
	virtual void update() {}
};

#endif /* GRAPHICS_TERRAIN_DSTERRAINGENERATIONSYSTEM_H_ */
