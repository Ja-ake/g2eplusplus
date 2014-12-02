#ifndef GRAPHICS_NOCLIPCAMERASYSTEM_H_
#define GRAPHICS_NOCLIPCAMERASYSTEM_H_

#include <g2e/core/abstractsystem.h>
#include <g2e/event/eventlistener.h>
#include <g2e/event/event.h>

class NoClipCameraSystem : public g2e::AbstractSystem, public g2e::event::EventListener {
public:
	CLASSNAME(NoClipCameraSystem)

	NoClipCameraSystem();
	virtual ~NoClipCameraSystem();

	virtual void initialize(g2e::AbstractEntity*);
	virtual void initialize();
	virtual void update(g2e::AbstractEntity*);
	virtual void update();
	virtual void onEvent(g2e::event::Event*);
};

#endif /* GRAPHICS_NOCLIPCAMERASYSTEM_H_ */
