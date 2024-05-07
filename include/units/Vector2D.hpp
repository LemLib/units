#pragma once

#include "units/units.hpp"

namespace units {

static inline Angle constrainAngle(Angle in) { return mod(in, 1_rot); }

template <isQuantity T> class Vector2D {
    protected:
        T x, y;
    public:
        Vector2D() : x(0.0), y(0.0) {}

        Vector2D(T nx, T ny) : x(nx), y(ny) {}

        static Vector2D fromPolar(Angle t, T m) {
            m = m.abs();
            t = constrainAngle(t);
            return Vector2D<T>(m * cos(t), m * sin(t));
        }

        static Vector2D unitVector(Angle t) { return fromPolar(t, (T)1.0); }

        T getX() { return x; }

        T getY() { return y; }

        Vector2D<T> operator+(Vector2D<T>& other) { return Vector2D<T>(x + other.getX(), y + other.getY()); }

        Vector2D<T> operator-(Vector2D<T>& other) { return Vector2D<T>(x - other.getX(), y - other.getY()); }

        Vector2D<T> operator*(double factor) { return Vector2D<T>(x * factor, y * factor); }

        Vector2D<T> operator/(double factor) { return Vector2D<T>(x / factor, y / factor); }

        Vector2D<T>& operator+=(Vector2D<T>& other) {
            x += other.getX();
            y += other.getY();
            return (*this);
        }

        Vector2D<T>& operator-=(Vector2D<T>& other) {
            x -= other.getx();
            y -= other.getY();
            return (*this);
        }

        Vector2D<T>& operator*=(double factor) {
            x *= factor;
            y *= factor;
            return (*this);
        }

        Vector2D<T>& operator/=(double factor) {
            x /= factor;
            y /= factor;
            return (*this);
        }

        template <isQuantity Q, isQuantity R = QMultiplication<T, Q>> R dot(Vector2D<Q>& other) { return (x * other.x) + (y * other.y); }

        Angle theta() { return atan2(y, x); }

        T magnitude() { return sqrt(square(x) + square(y)); }

        Vector2D<T> vectorTo(Vector2D<T>& other) { return Vector2D<T>(other.x - x, other.y - y); }

        Angle angleTo(Vector2D<T>& other) { return atan2(other.y - y, other.x - x); }

        T distance(Vector2D<T>& other) { return sqrt(square(x - other.x, 2) + square(y - other.y, 2)); }

        Vector2D<T> normalize() {
            T m = magnitude();
            return Vector2D<T>(x / m, y / m);
        }

        void rotateBy(Angle angle) {
            T m = magnitude();
            Angle t = theta() + angle;
            x = m * cos(t);
            y = m * sin(t);
        }

        void rotateTo(Angle angle) {
            T m = magnitude();
            x = m * cos(angle);
            y = m * sin(angle);
        }

        Vector2D<T> rotatedBy(Angle angle) {
            T m = magnitude();
            Angle t = theta() + angle;
            return fromPolar(t, m);
        }

        Vector2D<T> rotatedTo(Angle angle) {
            T m = magnitude();
            return fromPolar(angle, m);
        }
};

typedef Vector2D<Length> V2Position;
typedef Vector2D<LinearVelocity> V2Velocity;
typedef Vector2D<LinearAcceleration> V2Acceleration;
typedef Vector2D<Force> V2Force;
} // namespace units