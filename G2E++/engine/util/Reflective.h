/*
 * Reflective.h
 *
 *  Created on: Nov 21, 2014
 *      Author: Jake
 */

#ifndef UTIL_REFLECTIVE_H_
#define UTIL_REFLECTIVE_H_

#include <string>
#include <stdexcept>

namespace g2e {
namespace util {

class Reflective {
public:
	virtual ~Reflective();
	virtual std::string getClass();
};

} /* namespace util */
} /* namespace g2e */

#endif /* UTIL_REFLECTIVE_H_ */
