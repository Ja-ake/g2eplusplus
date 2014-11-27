#ifndef G2E_SERVICE_SERVICELOCATOR_H_
#define G2E_SERVICE_SERVICELOCATOR_H_

#include <vector>
#include <stdexcept>
#include "../../g2e/service/Service.h"

namespace g2e {
namespace service {

class ServiceLocator {
public:
	ServiceLocator();
	virtual ~ServiceLocator();

	Service* get(std::string);

//	template <class T>
//	g2e::service::Service& operator()();

	void add(g2e::service::Service*);
private:
	std::vector<g2e::service::Service*> services;
};

} /* namespace service */
} /* namespace g2e */

#endif /* G2E_SERVICE_SERVICELOCATOR_H_ */
