/*
 * Event.cpp
 *
 *  Created on: Nov 18, 2014
 *      Author: Jake
 */

#include "Event.h"

namespace g2e {

Event::Event() {
}

Event::~Event() {
}

template <class E> E Event::cast() {
	E* casted = dynamic_cast<E*>(this);
	if (casted != 0) return casted;
	else throw new std::runtime_error("Event cannot be casted.");
}

} /* namespace g2e */
