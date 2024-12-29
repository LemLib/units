#pragma once

#include "units/units.hpp"

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

// -15_cDeg == 105_stDeg
// 15_cDeg == 75_stDeg

// in order to do conversions properly between angles in standard position and compass angles, we need this helper class
// it can only be constructed through string literals
class CAngle : public Quantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>, std::ratio<0>,
                               std::ratio<0>, std::ratio<0>> {
        // make string literals friends, so they have access to the constructor
        friend constexpr CAngle operator""_cRad(long double value);
        friend constexpr CAngle operator""_cRad(unsigned long long value);
        friend constexpr CAngle operator""_cDeg(long double value);
        friend constexpr CAngle operator""_cDeg(unsigned long long value);
        friend constexpr CAngle operator""_cRot(long double value);
        friend constexpr CAngle operator""_cRot(unsigned long long value);
        friend constexpr CAngle operator*(double multiple, CAngle quantity);
        friend constexpr CAngle operator*(CAngle quantity, double multiple);
        friend constexpr CAngle operator/(double multiple, CAngle quantity);
        friend constexpr CAngle operator/(CAngle quantity, double multiple);
    public:
        // make CAngle able to be implicitly converted to Angle
        constexpr operator Angle() const { return Angle(M_PI_2 - this->value); }

        constexpr CAngle operator-() const { return CAngle(-this->value); }

        constexpr CAngle operator+() const { return CAngle(this->value); }
    private:
        // only allow construction through literals
        constexpr CAngle(double value)
            : Quantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>, std::ratio<0>,
                       std::ratio<0>, std::ratio<0>>(value) {}

        constexpr CAngle(Angle value)
            : Quantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>, std::ratio<0>,
                       std::ratio<0>, std::ratio<0>>(value) {}
};

constexpr bool operator==(Angle lhs, CAngle rhs) { return lhs == Angle(rhs); }

inline std::ostream& operator<<(std::ostream& os, const Angle& quantity) {
    os << quantity.internal() << " rad";
    return os;
}

constexpr CAngle operator*(double multiple, CAngle quantity) { return CAngle(multiple * quantity.internal()); }

constexpr CAngle operator*(CAngle quantity, double multiple) { return CAngle(multiple * quantity.internal()); }

constexpr CAngle operator/(CAngle quantity, double multiple) { return CAngle(quantity.internal() / multiple); }

constexpr Angle rad = Angle(1.0);
constexpr Angle deg = Angle(M_PI / 180);
constexpr Angle rot = Angle(M_TWOPI);

NEW_UNIT(AngularVelocity, radps, 0, 0, -1, 0, 1, 0, 0, 0)
NEW_UNIT_LITERAL(AngularVelocity, degps, deg / sec)
NEW_UNIT_LITERAL(AngularVelocity, rps, rot / sec)
NEW_UNIT_LITERAL(AngularVelocity, rpm, rot / min)

NEW_UNIT(AngularAcceleration, radps2, 0, 0, -2, 0, 1, 0, 0, 0)
NEW_UNIT_LITERAL(AngularAcceleration, degps2, deg / sec / sec)
NEW_UNIT_LITERAL(AngularAcceleration, rps2, rot / sec / sec)
NEW_UNIT_LITERAL(AngularAcceleration, rpm2, rot / min / min)

NEW_UNIT(AngularJerk, radps3, 0, 0, -3, 0, 1, 0, 0, 0)
NEW_UNIT_LITERAL(AngularJerk, rps3, rot / sec / sec / sec)
NEW_UNIT_LITERAL(AngularJerk, rpm3, rot / min / min / min)

// Angle declaration operators
// Standard orientation
constexpr Angle operator""_stRad(long double value) { return Angle(static_cast<double>(value)); }

constexpr Angle operator""_stRad(unsigned long long value) { return Angle(static_cast<double>(value)); }

constexpr Angle operator""_stDeg(long double value) { return static_cast<double>(value) * deg; }

constexpr Angle operator""_stDeg(unsigned long long value) { return static_cast<double>(value) * deg; }

constexpr Angle operator""_stRot(long double value) { return static_cast<double>(value) * rot; }

constexpr Angle operator""_stRot(unsigned long long value) { return static_cast<double>(value) * rot; }

// Compass orientation
constexpr CAngle operator""_cRad(long double value) { return CAngle(static_cast<double>(value)); }

constexpr CAngle operator""_cRad(unsigned long long value) { return CAngle(static_cast<double>(value)); }

constexpr CAngle operator""_cDeg(long double value) { return CAngle(static_cast<double>(value) * deg.internal()); }

constexpr CAngle operator""_cDeg(unsigned long long value) {
    return CAngle(static_cast<double>(value) * deg.internal());
}

constexpr CAngle operator""_cRot(long double value) { return CAngle(static_cast<double>(value) * rot.internal()); }

constexpr CAngle operator""_cRot(unsigned long long value) {
    return CAngle(static_cast<double>(value) * rot.internal());
}

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

static inline Angle constrainAngle360(Angle in) { return mod(in, rot); }

static inline Angle constrainAngle180(Angle in) {
    in = mod(in + 180 * deg, rot);
    return in < Angle(0) ? in + 180 * deg : in - 180 * deg;
}
} // namespace units

// Angle to/from operators
// Standard orientation
constexpr inline Angle from_stRad(double value) { return Angle(value); }

constexpr inline Angle from_stRad(Number value) { return Angle(value.internal()); }

constexpr inline double to_stRad(Angle quantity) { return quantity.internal(); }

constexpr inline Angle from_stDeg(double value) { return value * deg; }

constexpr inline Angle from_stDeg(Number value) { return value * deg; }

constexpr inline double to_stDeg(Angle quantity) { return quantity.convert(deg); }

constexpr inline Angle from_stRot(double value) { return value * rot; }

constexpr inline Angle from_stRot(Number value) { return value * rot; }

constexpr inline double to_stRot(Angle quantity) { return quantity.convert(rot); }

// Compass orientation
constexpr inline Angle from_cRad(double value) { return 90 * deg - Angle(value); }

constexpr inline Angle from_cRad(Number value) { return 90 * deg - Angle(value.internal()); }

constexpr inline double to_cRad(Angle quantity) { return quantity.internal(); }

constexpr inline Angle from_cDeg(double value) { return (90 - value) * deg; }

constexpr inline Angle from_cDeg(Number value) { return (90 - value.internal()) * deg; }

constexpr inline double to_cDeg(Angle quantity) { return (90 * deg - quantity).convert(deg); }

constexpr inline Angle from_cRot(double value) { return (90 - value) * deg; }

constexpr inline Angle from_cRot(Number value) { return (90 - value.internal()) * deg; }

constexpr inline double to_cRot(Angle quantity) { return (90 * deg - quantity).convert(rot); }