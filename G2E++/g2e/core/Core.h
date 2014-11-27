#ifndef G2E_CORE_CORE_H_
#define G2E_CORE_CORE_H_

#include "g2e/core/abstractentity.h"

#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include "../../g2e/core/AbstractSystem.h"
#include "../../g2e/service/ServiceLocator.h"

namespace g2e {

class Core {
public:
	static void initialize(g2e::AbstractSystem*);
	static void run();

	static void add(g2e::AbstractSystem*);
	static g2e::AbstractSystem* get(std::string);

	static g2e::service::ServiceLocator& service() { return serviceLocator; }
	static void addDefaultServices();

	static void done() { done_ = true; }
private:
	Core() {}

	static g2e::service::ServiceLocator serviceLocator;
	static std::map<std::string, g2e::AbstractSystem*> systems;

	static bool done_;
};

} /* namespace g2e */

#endif /* G2E_CORE_CORE_H_ */
