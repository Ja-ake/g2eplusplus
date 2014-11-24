/*
 * Vector3.h
 *
 *  Created on: Nov 20, 2014
 *      Author: Jake
 */

#ifndef MATH_VECTOR3_H_
#define MATH_VECTOR3_H_

#include "G2EMath.h"
#include <assert.h>

namespace g2e {
namespace math {

class Vector3 {
public:
	const double x() const { return x_; }
	const double y() const { return y_; }
	const double z() const { return z_; }

	Vector3() : Vector3(0.0L, 0.0L, 0.0L) { };
	Vector3(const Vector3& old) : Vector3(old.x(), old.y(), old.z()) { }
	Vector3(double xn, double yn, double zn) : x_(xn), y_(yn), z_(zn) { }
	~Vector3();

	const Vector3& add(const Vector3&) const;
	const Vector3& cross(const Vector3&) const;
	const Vector3& spherical() const;
	const double dot(const Vector3&) const;
	const double length() const;
	const double lengthSquared() const;
	const Vector3& multiply(double) const;
	const Vector3& normal() const;
	const Vector3& normalize() const;
	const Vector3& reverse() const;
	const Vector3& withLength(double) const;
	const Vector3& withX(double) const;
	const Vector3& withY(double) const;
	const Vector3& withZ(double) const;
	const Vector3& subtract(const Vector3) const;

	const Vector3& operator+(const Vector3& other) const { return this->add(other); }
	const Vector3& operator-(const Vector3& other) const { return this->subtract(other); }
	const Vector3& operator*(double length) const { return this->multiply(length); }
	const Vector3& operator/(double length) const { assert(length>0); return this->multiply(1/length); }

private:
	double x_, y_, z_;
};

} /* namespace math */
} /* namespace g2e */

#endif /* MATH_VECTOR3_H_ */
