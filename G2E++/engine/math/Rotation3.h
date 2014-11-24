/*
 * Rotation3.h
 *
 *  Created on: Nov 20, 2014
 *      Author: Jake
 */

#ifndef MATH_ROTATION3_H_
#define MATH_ROTATION3_H_

namespace g2e {
namespace math {

class Rotation3 {
public:
	Rotation3();
	virtual ~Rotation3();

private:
	double yaw, pitch, roll;
};

} /* namespace math */
} /* namespace g2e */

#endif /* MATH_ROTATION3_H_ */
