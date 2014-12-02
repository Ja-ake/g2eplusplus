#ifndef PHYSICS_MOVEMENT_VELOCITYSYSTEM_H_
#define PHYSICS_MOVEMENT_VELOCITYSYSTEM_H_

#include <g2e/core/abstractsystem.h>

class VelocitySystem : public g2e::AbstractSystem {
public:
	CLASSNAME(VelocitySystem)

	VelocitySystem();
	virtual ~VelocitySystem();

	virtual void initialize(g2e::AbstractEntity*) {}
	virtual void initialize() {}
	virtual void update(g2e::AbstractEntity*);
	virtual void update() {}
};

#endif /* PHYSICS_MOVEMENT_VELOCITYSYSTEM_H_ */
