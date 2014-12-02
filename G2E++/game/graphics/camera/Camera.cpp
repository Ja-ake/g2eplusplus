#include <game/graphics/camera/Camera.h>

#include "../../physics/positioncomponent.h"
#include "../../physics/movement/velocitycomponent.h"
#include "../../physics/rotationcomponent.h"

Camera::Camera() {
}

Camera::~Camera() {
}

void Camera::initialize() {
	this->add(new PositionComponent(50.0f, 0.0f, 0.0f));
	this->add(new VelocityComponent(0.0f, 0.0f, 0.0f));
	this->add(new RotationComponent(-90.0f, 0.0f, 0.0f));
}
