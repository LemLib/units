#pragma once

#include "units/Angle.hpp"
#include <array>

namespace units {
/**
 * @class Vector2D
 *
 * @brief a 2D vector with x and y components of a given quantity type.
 *
 * @tparam T the type of quantity to use for the vector components
 */
template <size_t N, isQuantity T> class Vector {
    protected:
        std::array<T, N> vec {};
    public:
        Vector() {}

        Vector(T x)
            requires(N == 1)
            : vec({std::move(x)}) {}

        Vector(T x, T y)
            requires(N == 2)
            : vec({std::move(x), std::move(y)}) {}

        Vector(T x, T y, T z)
            requires(N == 3)
            : vec({std::move(x), std::move(y), std::move(z)}) {}

        Vector(std::array<T, N> _vec): vec(_vec) {}

        /**
         * @brief get the x component
         *
         * @return T x component
         */
        T getX() requires(N >= 1) { return vec[0]; }

        /**
         * @brief get the y component
         *
         * @return T y component
         */
        T getY() requires(N >= 2) { return vec[1]; }

        /**
         * @brief get the z component
         *
         * @return T z component
         */
        T getZ() requires(N >= 3) { return vec[2]; }

        /**
         * @brief set the x component
         *
         * @param nx x component
         */
        void setX(T nx) requires(N >= 2) { vec[0] = nx; }

        /**
         * @brief set the y component
         *
         * @param ny y component
         */
        void setY(T ny) requires(N >= 2) { vec[1] = ny; }

        /**
         * @brief set the z component
         *
         * @param nz z component
         */
        void setZ(T ny) requires(N >= 3) { vec[2] = ny; }

        /**
         * @brief += operator overload
         *
         * This operator adds the x and y components of two vectors and stores the result in the calling vector
         * {a, b} += {c, d} => {a + c, b + d}
         *
         * @param other vector to add
         * @return Vector<N, T>&
         */
        Vector<N, T>& operator+=(Vector<N, T>& other) {
            for (size_t i = 0; i < vec.size(); i++) {
                vec[i] += other.vec[i];
            }
            return (*this);
        }

        /**
         * @brief -= operator overload
         *
         * This operator subtracts the x and y components of two vectors and stores the result in the calling vector
         * {a, b} -= {c, d} => {a - c, b - d}
         *
         * @param other vector to subtract
         * @return Vector<N, T>&
         */
        Vector<N, T>& operator-=(Vector<N, T>& other) {
            for (size_t i = 0; i < vec.size(); i++) {
                vec[i] -= other.vec[i];
            }
            return (*this);
        }

        /**
         * @brief *= operator overload
         *
         * This operator multiplies the x and y components of a vector by a scalar and stores the result in the
         * calling vector
         * a *= {b, c} => {a * b, a * c}
         *
         * @param factor scalar to multiply by
         * @return Vector<N, T>&
         */
        Vector<N, T>& operator*=(double factor) {
            for (size_t i = 0; i < vec.size(); i++) {
                vec[i] *= factor;
            }
            return (*this);
        }

        /**
         * @brief /= operator overload
         *
         * This operator divides the x and y components of a vector by a scalar and stores the result in the
         * calling vector
         * {a, b} /= c => {a / c, b / c}
         *
         * @param factor scalar to divide by
         * @return Vector<N, T>&
         */
        Vector<N, T>& operator/=(double factor) {
            for (size_t i = 0; i < vec.size(); i++) {
                vec[i] /= factor;
            }
            return (*this);
        }

        /**
         * @brief + operator overload
         *
         * This operator adds the x and y components of two vectors
         * {a, b} + {c, d} = {a + c, b + d}
         *
         * @param other vector to add
         * @return Vector<N, T>
         */
        Vector<N, T> operator+(Vector<N, T>& other) { return (Vector<N, T>(other) += *this); }

        /**
         * @brief - operator overload
         *
         * This operator subtracts the x and y components of two vectors
         * {a, b} - {c, d} = {a - c, b - d}
         *
         * @param other vector to subtract
         * @return Vector<N, T>
         */
        Vector<N, T> operator-(Vector<N, T>& other) { return (Vector<N, T>(other) += *this); }

        /**
         * @brief * operator overload
         *
         * This operator multiplies the x and y components of a vector by a scalar
         * a * {b, c} = {a * b, a * c}
         *
         * @param factor scalar to multiply by
         * @return Vector<N, T>
         */
        Vector<N, T> operator*(double factor) { return (Vector<N, T>(*this) *= factor); }

        /**
         * @brief / operator overload
         *
         * This operator divides the x and y components of a vector by a scalar
         * {a, b} / c = {a / c, b / c}
         *
         * @param factor scalar to divide by
         * @return Vector<N, T>
         */
        Vector<N, T> operator/(double factor) { return (Vector<N, T>(*this) /= factor); }
};
} // namespace units