#include <game/physics/movement/VelocitySystem.h>

#include "../positioncomponent.h"
#include "velocitycomponent.h"

#include <g2e/core/core.h>
#include <g2e/time/timeservice.h>

#include <iostream>

using g2e::Core;
using g2e::time::TimeService;

using std::cout;
using std::endl;

VelocitySystem::VelocitySystem() {
}

VelocitySystem::~VelocitySystem() {
}

void VelocitySystem::update(g2e::AbstractEntity* entity) {
	PositionComponent* position = (PositionComponent*) entity->get("PositionComponent");
	VelocityComponent* velocity = (VelocityComponent*) entity->get("VelocityComponent");
	position->position = position->position + (velocity->velocity * ((TimeService*)Core::service().get("TimeService"))->getInterval());

//	cout << "tick: " << ((TimeService*)Core::service().get("TimeService"))->getInterval() << endl;
}
