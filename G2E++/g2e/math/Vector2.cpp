/*
 * Vector2.cpp
 *
 *  Created on: Nov 19, 2014
 *      Author: Jake
 */

#include "../../g2e/math/Vector2.h"

namespace g2e {
namespace math {

Vector2::~Vector2() {
}

const Vector2& Vector2::add(const Vector2& other) const {
    return Vector2(x() + other.x(), y() + other.y());
}

const double Vector2::cross(const Vector2& other) const {
    return x() * other.y() - y() * other.x();
}

const double Vector2::direction() const {
    return atan2(y(), x());
}

const double Vector2::dot(const Vector2& other) const {
    return x() * other.x() + y() * other.y();
}

const double Vector2::length() const {
    return sqrt(lengthSquared());
}

const double Vector2::lengthSquared() const {
    return x() * x() + y() * y();
}

const Vector2& Vector2::multiply(double d) const {
    return Vector2(x() * d, y() * d);
}

const Vector2& Vector2::normal() const {
    return Vector2(-y(), x());
}

const Vector2& Vector2::normalize() const {
    return multiply(1 / length());
}

const Vector2& Vector2::reverse() const {
    return Vector2(-x(), -y());
}

const Vector2& Vector2::withLength(double l) const {
    return multiply(l / length());
}

const Vector2& Vector2::withX(double xn) const {
    return Vector2(xn, y());
}

const Vector2& Vector2::withY(double yn) const {
    return Vector2(x(), yn);
}

const Vector2& Vector2::subtract(const Vector2 other) const {
    return Vector2(x() - other.x(), y() - other.y());
}

}
} /* namespace g2e */
