/*
 * Reflective.cpp
 *
 *  Created on: Nov 21, 2014
 *      Author: Jake
 */

#include "../../g2e/util/Reflective.h"

namespace g2e {
namespace util {

Reflective::~Reflective() {

}

std::string Reflective::getClass() {
	throw new std::runtime_error("Class has not defined itself.");
}

} /* namespace util */
} /* namespace g2e */
