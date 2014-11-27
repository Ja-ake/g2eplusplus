/*
 * Vector3.cpp
 *
 *  Created on: Nov 20, 2014
 *      Author: Jake
 */

#include "../../g2e/math/Vector3.h"

namespace g2e {
namespace math {

Vector3::~Vector3() {

}

const Vector3& Vector3::add(const Vector3& other) const {
	return Vector3(x() + other.x(), y() + other.y(), z() + other.z());
}

const Vector3& Vector3::cross(const Vector3& other) const {
	// a × b = {y1 z2 - z1 y2; z1 x2 - x1 z2; x1 y2 - y1 x2}
	return Vector3(y()*other.z()-z()*other.y(), z()*other.x()-x()*other.z(), x()*other.y()-y()*other.x());
}

const Vector3& Vector3::spherical() const {
	return Vector3(length(), cos(x()), sin(y()));
}

const double Vector3::dot(const Vector3& other) const {
	// a . b = {x1 x2 + y1 y2 + z1 z2}
	return x()*other.x() + y()*other.y() + z()*other.z();
}

const double Vector3::length() const {
	return sqrt(x()*x()+y()*y()+z()*z());
}

const double Vector3::lengthSquared() const {
	return x()*x()+y()*y()+z()*z();
}

const Vector3& Vector3::multiply(double factor) const {
	return Vector3(x()*factor, y()*factor, z()*factor);
}

const Vector3& Vector3::normal() const {
	return this->cross(this->subtract(Vector3(0.0, 0.0, -1.0))).withLength(this->length());
}

const Vector3& Vector3::normalize() const {
	double inverseLength = 1/length();
	return multiply(inverseLength);
}

const Vector3& Vector3::reverse() const {
	return multiply(-1);
}

const Vector3& Vector3::withLength(double newLength) const {
	double inverseLengthNew = (1/length())*newLength;
	return multiply(inverseLengthNew);
}

const Vector3& Vector3::withX(double xn) const {
	return Vector3(xn, y(), z());
}

const Vector3& Vector3::withY(double yn) const {
	return Vector3(x(), yn, z());
}

const Vector3& Vector3::withZ(double zn) const {
	return Vector3(x(), y(), zn);
}

const Vector3& Vector3::subtract(const Vector3 other) const {
	return Vector3(x()-other.x(), y()-other.y(), z()-other.z());
}

} /* namespace math */
} /* namespace g2e */
