#ifndef PHYSICS_TARGETCOMPONENT_H_
#define PHYSICS_TARGETCOMPONENT_H_

#include <g2e/core/abstractcomponent.h>
#include <g2e/math/vector3.h>

class TargetComponent : public g2e::AbstractComponent {
public:
	CLASSNAME(TargetComponent)

	TargetComponent() : TargetComponent(g2e::math::Vector3(0.0f, 0.0f, 0.0f)) {}
	TargetComponent(double x, double y, double z) :
		TargetComponent(g2e::math::Vector3(x, y, z)) {}
	TargetComponent(g2e::math::Vector3 p) { target = p; }
	virtual ~TargetComponent();

	g2e::math::Vector3 target;
};

#endif /* PHYSICS_TARGETCOMPONENT_H_ */
