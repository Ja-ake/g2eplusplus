#ifndef PHYSICS_ROTATIONCOMPONENT_H_
#define PHYSICS_ROTATIONCOMPONENT_H_

#include <g2e/core/abstractcomponent.h>
#include <g2e/math/rotation3.h>

class RotationComponent : public g2e::AbstractComponent {
public:
	CLASSNAME(RotationComponent)

	RotationComponent() : RotationComponent(0.0f, 0.0f, 0.0f) {}
	RotationComponent(double p, double y, double r) : RotationComponent(g2e::math::Rotation3(p, y, r)) {}
	RotationComponent(g2e::math::Rotation3 r) : rotation(r) {}
	virtual ~RotationComponent();

	g2e::math::Rotation3 rotation;
};

#endif /* PHYSICS_ROTATIONCOMPONENT_H_ */
