/*
 * AbstractComponent.h
 *
 *  Created on: Nov 21, 2014
 *      Author: Jake
 */

#ifndef CORE_ABSTRACTCOMPONENT_H_
#define CORE_ABSTRACTCOMPONENT_H_

#include "util/reflective.h"

#include <string>

namespace g2e {

class AbstractComponent : public g2e::util::Reflective {
public:
	virtual std::string getClass()=0;

	AbstractComponent();
	virtual ~AbstractComponent();

	virtual void initialize()=0;
};

} /* namespace g2e */

#endif /* CORE_ABSTRACTCOMPONENT_H_ */
