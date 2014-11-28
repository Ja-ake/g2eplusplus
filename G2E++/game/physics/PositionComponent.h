#ifndef PHYSICS_POSITIONCOMPONENT_H_
#define PHYSICS_POSITIONCOMPONENT_H_

#include <g2e/core/abstractcomponent.h>
#include <glm/glm.hpp>

class PositionComponent : public g2e::AbstractComponent {
public:
	PositionComponent() : PositionComponent(glm::vec3(0.0f, 0.0f, 0.0f)) {}
	PositionComponent(double x, double y, double z) :
		PositionComponent(glm::vec3(x, y, z)) {}
	PositionComponent(glm::vec3 p) { position = p; }
	virtual ~PositionComponent();
	virtual std::string getClass() { return "PositionComponent"; }

	glm::vec3 position;
};

#endif /* PHYSICS_POSITIONCOMPONENT_H_ */
