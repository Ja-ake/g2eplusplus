#include "../../g2e/core/Core.h"

#include "g2e/gl/openglservice.h"
#include "g2e/event/eventservice.h"
#include "g2e/resource/resourceloaderservice.h"
#include "g2e/time/timeservice.h"
#include "g2e/service/service.h"

namespace g2e {

g2e::service::ServiceLocator Core::serviceLocator;
std::map<std::string, g2e::AbstractSystem*> Core::systems;

bool Core::done_ = false;

void Core::initialize(g2e::AbstractSystem* initializer) {
	initializer->initialize();
	std::vector<AbstractEntity*> entities = initializer->getEntityList();
	for (auto i=entities.begin(); i!=entities.end(); i++) initializer->update(*i);
	initializer->update();
}

void Core::run() {
	while (!done_) {
		std::vector<g2e::service::Service*>& services = Core::serviceLocator.getAll();
		for (auto i = services.begin(); i != services.end(); i++) {
			if (*i != nullptr) ((g2e::service::Service*)*i)->update();
		}

		for (auto i = systems.begin(); i != systems.end(); i++) {
			AbstractSystem* system = (*i).second;
			std::vector<AbstractEntity*> entities = system->getEntityList();
			for (auto j = entities.begin(); j != entities.end(); j++)
				system->update(*j);
			system->update();
		}
	}
}

void Core::add(g2e::AbstractSystem* ns) {
	systems[ns->getClass()] = ns;
	ns->initialize();
}

g2e::AbstractSystem* Core::get(std::string name) {
	if (systems[name] != 0) return systems[name];
	else throw std::runtime_error("Invalid system.");
}

void Core::addDefaultServices() {
	Core::service().add(new g2e::gl::OpenGLService());
	Core::service().add(new g2e::event::EventService());
	Core::service().add(new g2e::io::ResourceLoaderService());
	Core::service().add(new g2e::time::TimeService());
}

} /* namespace g2e */
