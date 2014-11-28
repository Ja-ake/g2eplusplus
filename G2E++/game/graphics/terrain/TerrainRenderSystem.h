#ifndef GRAPHICS_WORLDRENDERSYSTEM_H_
#define GRAPHICS_WORLDRENDERSYSTEM_H_

#include <g2e/core/abstractsystem.h>
#include <g2e/gl/openglservice.h>

class TerrainRenderSystem : public g2e::AbstractSystem {
public:
	TerrainRenderSystem();
	virtual ~TerrainRenderSystem();
	virtual std::string getClass() { return "TerrainRenderSystem"; }

	virtual void initialize();
	virtual void update();
	virtual void initialize(g2e::AbstractEntity*);
	virtual void update(g2e::AbstractEntity*);
};

#endif /* GRAPHICS_WORLDRENDERSYSTEM_H_ */
