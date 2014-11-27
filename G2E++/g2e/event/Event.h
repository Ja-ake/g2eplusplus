/*
 * Event.h
 *
 *  Created on: Nov 18, 2014
 *      Author: Jake
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <stdexcept>
#include <string>
#include "../../g2e/util/Reflective.h"

namespace g2e {
namespace event {

class Event : public g2e::util::Reflective {
public:
	virtual std::string getClass() = 0;

	Event();
	virtual ~Event();
};

} /* namespace event */
} /* namespace g2e */

#endif /* EVENT_H_ */
