#pragma once

#include "units.hpp"

class Angle : public Quantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>, std::ratio<0>,
                              std::ratio<0>, std::ratio<0>> {
    public:
        explicit constexpr Angle(double value)
            : Quantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>, std::ratio<0>,
                       std::ratio<0>, std::ratio<0>>(value) {}

        constexpr Angle(Quantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>,
                                 std::ratio<0>, std::ratio<0>, std::ratio<0>>
                            value)
            : Quantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>, std::ratio<0>,
                       std::ratio<0>, std::ratio<0>>(value) {};
};

template <> struct LookupName<Quantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>,
                                       std::ratio<0>, std::ratio<0>, std::ratio<0>>> {
        using Named = Angle;
};

inline std::ostream& operator<<(std::ostream& os, const Angle& quantity) {
    os << quantity.internal() << " rad";
    return os;
}

constexpr Angle Radian = Angle(1.0);
constexpr Angle Degree = Angle(M_PI / 180);
constexpr Angle Rotation = Angle(M_TWOPI);

NEW_UNIT(AngularVelocity, RadiansPerSecond, radps, 0, 0, -1, 0, 1, 0, 0, 0)
NEW_UNIT_LITERAL(AngularVelocity, DegreesPerSecond, degps, Degree / Second)
NEW_UNIT_LITERAL(AngularVelocity, RotationsPerSecond, rps, Rotation / Second)
NEW_UNIT_LITERAL(AngularVelocity, RotationsPerMinute, rpm, Rotation / Minute)

NEW_UNIT(AngularAcceleration, RadiansPerSecondSquared, radps2, 0, 0, -2, 0, 1, 0, 0, 0)
NEW_UNIT_LITERAL(AngularAcceleration, DegreesPerSecondSquared, degps2, Degree / (Second * Second))
NEW_UNIT_LITERAL(AngularAcceleration, RotationsPerSecondSquared, rps2, Rotation / (Second * Second))
NEW_UNIT_LITERAL(AngularAcceleration, RotationsPerMinuteSquared, rpm2, Rotation / (Minute * Minute))

NEW_UNIT(AngularJerk, RadiansPerSecondCubed, radps3, 0, 0, -3, 0, 1, 0, 0, 0)
NEW_UNIT_LITERAL(AngularJerk, DegreesPerSecondCubed, degps3, Degree / (Second * Second * Second))
NEW_UNIT_LITERAL(AngularJerk, RotationsPerSecondCubed, rps3, Rotation / (Second * Second * Second))
NEW_UNIT_LITERAL(AngularJerk, RotationsPerMinuteCubed, rpm3, Rotation / (Minute * Minute * Minute))

// Angle declaration operators
// Standard orientation
constexpr Angle operator""_stRad(long double value) { return Angle(static_cast<double>(value)); }

constexpr Angle operator""_stRad(unsigned long long value) { return Angle(static_cast<double>(value)); }

constexpr Angle operator""_stDeg(long double value) { return static_cast<double>(value) * Degree; }

constexpr Angle operator""_stDeg(unsigned long long value) { return static_cast<double>(value) * Degree; }

constexpr Angle operator""_stRot(long double value) { return static_cast<double>(value) * Rotation; }

constexpr Angle operator""_stRot(unsigned long long value) { return static_cast<double>(value) * Rotation; }

// Compass orientation
constexpr Angle operator""_cRad(long double value) { return 90_stDeg - Angle(static_cast<double>(value)); }

constexpr Angle operator""_cRad(unsigned long long value) { return 90_stDeg - Angle(static_cast<double>(value)); }

constexpr Angle operator""_cDeg(long double value) { return 90_stDeg - static_cast<double>(value) * Degree; }

constexpr Angle operator""_cDeg(unsigned long long value) { return 90_stDeg - static_cast<double>(value) * Degree; }

constexpr Angle operator""_cRot(long double value) { return 90_stDeg - static_cast<double>(value) * Rotation; }

constexpr Angle operator""_cRot(unsigned long long value) { return 90_stDeg - static_cast<double>(value) * Rotation; }

// Angle functions
namespace units {
constexpr Number sin(const Angle& rhs) { return Number(std::sin(rhs.internal())); }

constexpr Number cos(const Angle& rhs) { return Number(std::cos(rhs.internal())); }

constexpr Number tan(const Angle& rhs) { return Number(std::tan(rhs.internal())); }

template <isQuantity Q> constexpr Angle asin(const Q& rhs) { return Angle(std::asin(rhs.internal())); }

template <isQuantity Q> constexpr Angle acos(const Q& rhs) { return Angle(std::acos(rhs.internal())); }

template <isQuantity Q> constexpr Angle atan(const Q& rhs) { return Angle(std::atan(rhs.internal())); }

template <isQuantity Q> constexpr Angle atan2(const Q& lhs, const Q& rhs) {
    return Angle(std::atan2(lhs.internal(), rhs.internal()));
}

static inline Angle constrainAngle360(Angle in) { return mod(in, Rotation); }

static inline Angle constrainAngle180(Angle in) {
    in = mod(in + 180 * Degree, Rotation);
    return in < Angle(0) ? in + 180 * Degree : in - 180 * Degree;
}
} // namespace units

// Angle to/from operators
// Standard orientation
constexpr inline Angle from_stRad(double value) { return Angle(value); }

constexpr inline double to_stRad(Angle quantity) { return quantity.internal(); }

constexpr inline Angle from_stDeg(double value) { return value * Degree; }

constexpr inline double to_stDeg(Angle quantity) { return quantity.convert(Degree); }

constexpr inline Angle from_stRot(double value) { return value * Rotation; }

constexpr inline double to_stRot(Angle quantity) { return quantity.convert(Rotation); }

// Compass orientation
constexpr inline Angle from_cRad(double value) { return 90 * Degree - Angle(value); }

constexpr inline double to_cRad(Angle quantity) { return quantity.internal(); }

constexpr inline Angle from_cDeg(double value) { return (90 - value) * Degree; }

constexpr inline double to_cDeg(Angle quantity) { return (90 * Degree - quantity).convert(Degree); }

constexpr inline Angle from_cRot(double value) { return (90 - value) * Degree; }

constexpr inline double to_cRot(Angle quantity) { return (90 * Degree - quantity).convert(Rotation); }