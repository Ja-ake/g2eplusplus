#include "../../g2e/event/EventService.h"
#include <iostream>

using std::cout;
using std::endl;
using g2e::event::EventListener;

namespace g2e {
namespace event {

EventService::EventService() {
}

EventService::~EventService() {
}

void EventService::add(g2e::event::EventListener* l) {
	listeners.push_back(l);
}

void EventService::remove(g2e::event::EventListener* l) {
	for (auto i=listeners.begin(); i!=listeners.end(); i++) if (*i == l) listeners.erase(i);
}

void EventService::update() {
	for (auto e=eventQueue.begin(); e!=eventQueue.end(); e++) {
		for (auto l=listeners.begin(); l!=listeners.end(); l++) {
			if (*l != nullptr && *e != nullptr) ((EventListener*)*l)->onEvent(*e);
		}

		delete *e;
	}

//	cout << eventQueue.size() << listeners.size() << endl;

	eventQueue.clear();
}

void EventService::fire(g2e::event::Event* event) {
	eventQueue.push_back(event);
}

} /* namespace event */
} /* namespace g2e */
