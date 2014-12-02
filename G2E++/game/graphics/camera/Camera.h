#ifndef GRAPHICS_CAMERA_CAMERA_H_
#define GRAPHICS_CAMERA_CAMERA_H_

#include <g2e/core/abstractentity.h>

class Camera : public g2e::AbstractEntity {
public:
	CLASSNAME(Camera)

	Camera();
	virtual ~Camera();

	virtual void initialize();
};

#endif /* GRAPHICS_CAMERA_CAMERA_H_ */
