/*
 * Rotation3.h
 *
 *  Created on: Nov 20, 2014
 *      Author: Jake
 */

#ifndef G2E_MATH_ROTATION3_H_
#define G2E_MATH_ROTATION3_H_

namespace g2e {
namespace math {

class Rotation3 {
public:
	const double yaw() const { return _yaw; }
	const double pitch() const { return _pitch; }
	const double roll() const { return _roll; }

	Rotation3() : Rotation3(0.0L, 0.0L, 0.0L) {}
	Rotation3(double y, double p, double r) : _yaw(y), _pitch(p), _roll(r) {}
	~Rotation3();

	const Rotation3 add(Rotation3) const;
	const Rotation3 subtract(Rotation3) const;

	const Rotation3 operator+(Rotation3 other) const { return add(other); }
	const Rotation3 operator-(Rotation3 other) const { return subtract(other); }
private:
	double _yaw, _pitch, _roll;
};

} /* namespace math */
} /* namespace g2e */

#endif /* G2E_MATH_ROTATION3_H_ */
