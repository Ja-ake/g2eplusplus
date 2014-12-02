#ifndef PHYSICS_MOVEMENT_VELOCITYCOMPONENT_H_
#define PHYSICS_MOVEMENT_VELOCITYCOMPONENT_H_

#include <g2e/core/abstractcomponent.h>
#include <g2e/math/vector3.h>

class VelocityComponent : public g2e::AbstractComponent {
public:
	CLASSNAME(VelocityComponent)

	VelocityComponent() : VelocityComponent(g2e::math::Vector3(0.0f, 0.0f, 0.0f)) {}
	VelocityComponent(double x, double y, double z) : VelocityComponent(g2e::math::Vector3(x, y, z)) {}
	VelocityComponent(g2e::math::Vector3 v) : velocity(v) {}
	virtual ~VelocityComponent();

	g2e::math::Vector3 velocity;
};

#endif /* PHYSICS_MOVEMENT_VELOCITYCOMPONENT_H_ */
