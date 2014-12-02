/*
 * Rotation3.cpp
 *
 *  Created on: Nov 20, 2014
 *      Author: Jake
 */

#include "../../g2e/math/Rotation3.h"

namespace g2e {
namespace math {

Rotation3::~Rotation3() { }

const Rotation3 Rotation3::add(Rotation3 other) const {
	return Rotation3(this->yaw() + other.yaw(), this->pitch() + other.pitch(), this->roll() + other.roll());
}

const Rotation3 Rotation3::subtract(Rotation3 other) const {
	return Rotation3(this->yaw() - other.yaw(), this->pitch() - other.pitch(), this->roll() - other.roll());
}

} /* namespace math */
} /* namespace g2e */
