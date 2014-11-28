#ifndef GRAPHICS_TERRAIN_TERRAINCOMPONENT_H_
#define GRAPHICS_TERRAIN_TERRAINCOMPONENT_H_

#include <g2e/core/abstractcomponent.h>
#include <g2e/math/color.h>
#include <g2e/gl/openglservice.h>

class TerrainComponent : public g2e::AbstractComponent {
public:
	TerrainComponent() : TerrainComponent(256, 256) {}
	TerrainComponent(int, int);
	virtual ~TerrainComponent();
	virtual std::string getClass() { return "TerrainComponent"; }

	double** heightmap;
	g2e::math::Color** colormap;
	int width, height;
	g2e::gl::opengl_buffers buffer;
	g2e::gl::opengl_program program;
};

#endif /* GRAPHICS_TERRAIN_TERRAINCOMPONENT_H_ */
