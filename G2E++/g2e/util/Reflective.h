/*
 * Reflective.h
 *
 *  Created on: Nov 21, 2014
 *      Author: Jake
 */

#ifndef G2E_UTIL_REFLECTIVE_H_
#define G2E_UTIL_REFLECTIVE_H_

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

#endif /* G2E_UTIL_REFLECTIVE_H_ */
