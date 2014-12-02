#ifndef G2E_SERVICE_SERVICE_H_
#define G2E_SERVICE_SERVICE_H_

#include <string>
#include "../../g2e/util/Reflective.h"

namespace g2e {
namespace service {

class Service : public g2e::util::Reflective {
public:
	virtual std::string getClass() = 0;

	Service();
	virtual ~Service();

	virtual void update() {}
};

} /* namespace service */
} /* namespace g2e */

#endif /* G2E_SERVICE_SERVICE_H_ */
