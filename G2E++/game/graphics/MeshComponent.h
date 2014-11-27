#ifndef GRAPHICS_MESHCOMPONENT_H_
#define GRAPHICS_MESHCOMPONENT_H_

#include <g2e/core/abstractcomponent.h>
#include <g2e/gl/openglservice.h>

class MeshComponent : public g2e::AbstractComponent {
public:
	MeshComponent(int, double*);
	virtual ~MeshComponent();
	virtual std::string getClass() { return "MeshComponent"; }
	virtual void initialize() {}

	int size;
	double* vertices;
	g2e::gl::opengl_buffers buffers;
	g2e::gl::opengl_program program;
};

#endif /* GRAPHICS_MESHCOMPONENT_H_ */
