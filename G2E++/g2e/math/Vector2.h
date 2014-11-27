/*
 * Vector2.h
 *
 *  Created on: Nov 19, 2014
 *      Author: Jake
 */

#ifndef G2E_MATH_VECTOR2_H_
#define G2E_MATH_VECTOR2_H_

#include <assert.h>
#include "../../g2e/math/G2EMath.h"

namespace g2e {
namespace math {

class Vector2 {
public:
	const double x() const { return this->x_; }
	const double y() const { return this->y_; }

	Vector2() : Vector2(0.0, 0.0) { }
	Vector2(double xn, double yn) : x_(xn), y_(yn) { }
	virtual ~Vector2();

	const Vector2& add(const Vector2&) const;
	const double cross(const Vector2&) const;
	const double direction() const;
	const double dot(const Vector2&) const;
	const double length() const;
	const double lengthSquared() const;
	const Vector2& multiply(double) const;
	const Vector2& normal() const;
	const Vector2& normalize() const;
	const Vector2& reverse() const;
	const Vector2& withLength(double) const;
	const Vector2& withX(double) const;
	const Vector2& withY(double) const;
	const Vector2& subtract(const Vector2) const;

	const Vector2& operator+(const Vector2& other) const { return this->add(other); }
	const Vector2& operator-(const Vector2& other) const { return this->subtract(other); }
	const Vector2& operator*(double length) const { return this->multiply(length); }
	const Vector2& operator/(double length) const { assert(length>0); return this->multiply(1/length); }

private:
	const double x_, y_;
};

} /* namespace math */
} /* namespace g2e */

#endif /* G2E_MATH_VECTOR2_H_ */
