#ifndef GRAPHICS_TERRAIN_TERRAIN_H_
#define GRAPHICS_TERRAIN_TERRAIN_H_

#include <g2e/core/abstractentity.h>

class Terrain : public g2e::AbstractEntity {
public:
	CLASSNAME(Terrain)

	Terrain();
	virtual ~Terrain();

	virtual void initialize();
};

#endif /* GRAPHICS_TERRAIN_TERRAIN_H_ */
