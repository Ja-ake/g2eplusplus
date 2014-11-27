/*
 * AbstractComponent.h
 *
 *  Created on: Nov 21, 2014
 *      Author: Jake
 */

#ifndef G2E_CORE_ABSTRACTCOMPONENT_H_
#define G2E_CORE_ABSTRACTCOMPONENT_H_

#include <string>
#include "../../g2e/util/Reflective.h"

namespace g2e {

class AbstractComponent : public g2e::util::Reflective {
public:
	virtual std::string getClass()=0;

	AbstractComponent();
	virtual ~AbstractComponent();

	virtual void initialize()=0;
};

} /* namespace g2e */

#endif /* G2E_CORE_ABSTRACTCOMPONENT_H_ */
