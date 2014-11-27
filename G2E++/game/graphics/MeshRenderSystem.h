#ifndef GRAPHICS_MESHRENDERSYSTEM_H_
#define GRAPHICS_MESHRENDERSYSTEM_H_

#include "meshcomponent.h"

#include <g2e/core/abstractsystem.h>

class MeshRenderSystem : public g2e::AbstractSystem {
public:
	MeshRenderSystem();
	virtual ~MeshRenderSystem();
	virtual std::string getClass() { return "MeshRenderSystem"; }

	virtual void initialize(g2e::AbstractEntity*);
	virtual void initialize();
	virtual void update(g2e::AbstractEntity*);
	virtual void update();
};

#endif /* GRAPHICS_MESHRENDERSYSTEM_H_ */
