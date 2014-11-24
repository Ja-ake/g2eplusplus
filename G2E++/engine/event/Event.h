/*
 * Event.h
 *
 *  Created on: Nov 18, 2014
 *      Author: Jake
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <stdexcept>

namespace g2e {

class Event {
public:
	Event();
	virtual ~Event();

	template <class E> E cast();
};

} /* namespace g2e */

#endif /* EVENT_H_ */
