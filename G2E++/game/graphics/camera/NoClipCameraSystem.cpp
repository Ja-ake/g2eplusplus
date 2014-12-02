#include <game/graphics/camera/NoClipCameraSystem.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <g2e/event/user/mouseevent.h>
#include <g2e/event/user/keyboardevent.h>
#include <g2e/gl/openglservice.h>
#include <g2e/core/core.h>
#include <g2e/event/eventservice.h>
#include <g2e/time/timeservice.h>
#include <g2e/math/rotation3.h>
#include <g2e/math/vector3.h>

#include "../../physics/positioncomponent.h"
#include "../../physics/movement/velocitycomponent.h"
#include "../../physics/rotationcomponent.h"

#include <iostream>
#include <windows.h>
#include <cmath>

#define PI (3.141592653589793)
#define TORADIANS (PI/180.0f)

using std::string;
using g2e::event::MouseEvent;
using g2e::gl::OpenGLService;
using g2e::time::TimeService;
using g2e::Core;
using g2e::math::Rotation3;
using g2e::math::Vector3;
using g2e::event::KeyboardEvent;

using std::cout;
using std::endl;

NoClipCameraSystem::NoClipCameraSystem() {
}

NoClipCameraSystem::~NoClipCameraSystem() {
}

void NoClipCameraSystem::initialize(g2e::AbstractEntity*) {

}

void NoClipCameraSystem::initialize() {
	((g2e::event::EventService*)Core::service().get("EventService"))->add(this);
}

void NoClipCameraSystem::update(g2e::AbstractEntity* entity) {
	{
		POINT mouse;
		GetCursorPos(&mouse);

		double xoff = (double)mouse.x - 600, yoff = -((double)mouse.y - 450);
		for (auto i = this->entities.begin(); i!=this->entities.end(); i++) {
			RotationComponent* rc = (RotationComponent*) ((g2e::AbstractEntity*)*i)->get("RotationComponent");
			VelocityComponent* vc = (VelocityComponent*) ((g2e::AbstractEntity*)*i)->get("VelocityComponent");

			double xrot = xoff * 0.1f;
			double yrot = yoff * 0.1f;
			rc->rotation = rc->rotation + Rotation3(xrot, yrot, 0);

			double speed = vc->velocity.length();
			vc->velocity = Vector3(
					cos(rc->rotation.pitch()*TORADIANS)*cos(rc->rotation.yaw()*TORADIANS - PI/2),
					sin(rc->rotation.pitch()*TORADIANS),
					cos(rc->rotation.pitch()*TORADIANS)*sin(rc->rotation.yaw()*TORADIANS - PI/2)
				).withLength(speed);
		}

		if (mouse.x != 600 || mouse.y != 450) {
			SetCursorPos(600, 450);
		}
	}

	OpenGLService* opengl = (OpenGLService*) Core::service().get("OpenGLService");

	PositionComponent* pc = (PositionComponent*) entity->get("PositionComponent");
	RotationComponent* rc = (RotationComponent*) entity->get("RotationComponent");

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::rotate(view, (float)rc->rotation.yaw(), glm::vec3(0, 1, 0));
	view = glm::rotate(view, (float)-rc->rotation.pitch(), glm::vec3(cos(rc->rotation.yaw()*TORADIANS), 0, sin((rc->rotation.yaw()*TORADIANS))));
//	view *= glm::rotate(view, (float)rc->rotation.roll(), glm::vec3(0, 0, 1));
	view = glm::translate(view, glm::vec3(-pc->position.x(), -pc->position.y(), -pc->position.z()));

	opengl->setView(view);
}

void NoClipCameraSystem::update() {}

void NoClipCameraSystem::onEvent(g2e::event::Event* event) {
//	TimeService* time = (TimeService*) Core::service().get("TimeService");

	string classname = event->getClass();
//	if (classname == "MouseEvent") {
//		MouseEvent* mouse = (MouseEvent*) event;
//
//		double xoff = mouse->x - 592, yoff = -(mouse->y - 420);
////		if (xoff != 0 || yoff != 0) cout << xoff << " " << yoff << endl;
//		for (auto i = this->entities.begin(); i!=this->entities.end(); i++) {
//			RotationComponent* rc = (RotationComponent*) ((g2e::AbstractEntity*)*i)->get("RotationComponent");
//			VelocityComponent* vc = (VelocityComponent*) ((g2e::AbstractEntity*)*i)->get("VelocityComponent");
//
//			double xrot = xoff * 0.1f;
//			double yrot = yoff * 0.1f;
//			rc->rotation = rc->rotation + Rotation3(xrot, yrot, 0);
//
//			double speed = vc->velocity.length();
//			vc->velocity = Vector3(
//					cos(rc->rotation.pitch()*TORADIANS)*cos(rc->rotation.yaw()*TORADIANS - PI/2),
//					sin(rc->rotation.pitch()*TORADIANS),
//					cos(rc->rotation.pitch()*TORADIANS)*sin(rc->rotation.yaw()*TORADIANS - PI/2)
//				).withLength(speed);
////
////			cout << rc->rotation.pitch()*TORADIANS/PI << ", " << rc->rotation.yaw()*TORADIANS/PI << endl;
////			cout << vc->velocity.x() << ", " << vc->velocity.y() << ", " << vc->velocity.z() << endl;
////			cout << mouse->x - 592 << " " << mouse->y - 420 << endl;
////			vc->velocity = vc->velocity.withLength(speed);
//		}
//
//		if (mouse->x != 592 || mouse->y != 420) {
//			SetCursorPos(600, 450);
//		}
//
//		return;
//	}

	if (classname == "KeyboardEvent") {
		KeyboardEvent* keyboard = (KeyboardEvent*) event;
		for (auto i = this->entities.begin(); i!=this->entities.end(); i++) {
			VelocityComponent* vc = (VelocityComponent*) ((g2e::AbstractEntity*)*i)->get("VelocityComponent");
			RotationComponent* rc = (RotationComponent*) ((g2e::AbstractEntity*)*i)->get("RotationComponent");

			Vector3 direction;
			double speed = vc->velocity.length();

			if (keyboard->key == 'W') direction = Vector3(
					cos(rc->rotation.pitch()*TORADIANS)*cos(rc->rotation.yaw()*TORADIANS - PI/2),
					sin(rc->rotation.pitch()*TORADIANS),
					cos(rc->rotation.pitch()*TORADIANS)*sin(rc->rotation.yaw()*TORADIANS - PI/2)
				);

			if (keyboard->key == 'S') direction = Vector3(
					cos(rc->rotation.pitch()*TORADIANS)*cos(rc->rotation.yaw()*TORADIANS - PI/2),
					sin(rc->rotation.pitch()*TORADIANS),
					cos(rc->rotation.pitch()*TORADIANS)*sin(rc->rotation.yaw()*TORADIANS - PI/2)
				).multiply(-1);

			vc->velocity = vc->velocity.withLength(speed) + direction.withLength((keyboard->pressed ? 1 : -1) * 75.0f);
			cout << direction.x() << endl;
		}
	}
}
