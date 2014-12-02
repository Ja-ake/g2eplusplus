#ifndef PHYSICS_POSITIONCOMPONENT_H_
#define PHYSICS_POSITIONCOMPONENT_H_

#include <g2e/core/abstractcomponent.h>
#include <g2e/math/vector3.h>

class PositionComponent : public g2e::AbstractComponent {
public:
	PositionComponent() : PositionComponent(g2e::math::Vector3(0.0f, 0.0f, 0.0f)) {}
	PositionComponent(double x, double y, double z) :
		PositionComponent(g2e::math::Vector3(x, y, z)) {}
	PositionComponent(g2e::math::Vector3 p) { position = p; }
	virtual ~PositionComponent();
	virtual std::string getClass() { return "PositionComponent"; }

	g2e::math::Vector3 position;
};

#endif /* PHYSICS_POSITIONCOMPONENT_H_ */
