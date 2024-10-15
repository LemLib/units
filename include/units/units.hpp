#pragma once

#include <cmath>
#include <ratio>
#include <iostream>

// define M_PI if not already defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// define typenames

/**
 * @brief Quantity class
 *
 * This class is a template class that represents a quantity with a value and units.
 *
 * @tparam TYPENAMES the types of the units
 */
template <typename Mass = std::ratio<0>, typename Length = std::ratio<0>, typename Time = std::ratio<0>,
          typename Current = std::ratio<0>, typename Angle = std::ratio<0>, typename Temperature = std::ratio<0>,
          typename Luminosity = std::ratio<0>, typename Moles = std::ratio<0>>
class Quantity {
    protected:
        double value; /** the value stored in its base unit type */
    public:
        typedef Mass mass; /** mass unit type */
        typedef Length length; /** length unit type */
        typedef Time time; /** time unit type */
        typedef Current current; /** current unit type */
        typedef Angle angle; /** angle unit type */
        typedef Temperature temperature; /** temperature unit type */
        typedef Luminosity luminosity; /** luminosity unit type */
        typedef Moles moles; /** moles unit type */

        using Self = Quantity<Mass, Length, Time, Current, Angle, Temperature, Luminosity, Moles>;

        /**
         * @brief construct a new Quantity object
         *
         * This constructor initializes the value to 0
         */
        explicit constexpr Quantity() : value(0) {}

        /**
         * @brief construct a new Quantity object
         *
         * @param value the value to initialize the quantity with
         */
        explicit constexpr Quantity(double value) : value(value) {}

        /**
         * @brief construct a new Quantity object
         *
         * @param other the quantity to copy
         */
        constexpr Quantity(Self const& other) : value(other.value) {}

        /**
         * @brief get the value of the quantity in its base unit type
         *
         * @return constexpr double
         */
        constexpr double internal() const { return value; }

        // TODO: document this
        constexpr double convert(Self quantity) { return value / quantity.value; }

        /**
         * @brief set the value of this quantity to its current value plus another quantity
         *
         * @param other the quantity to add
         */
        constexpr void operator+=(Self other) { value += other.value; }

        /**
         * @brief set the value of this quantity to its current value minus another quantity
         *
         * @param other the quantity to subtract
         */
        constexpr void operator-=(Self other) { value -= other.value; }

        /**
         * @brief set the value of this quantity to its current value times a double
         *
         * @param multiple the multiple to multiply by
         */
        constexpr void operator*=(double multiple) { value *= multiple; }

        /**
         * @brief set the value of this quantity to its current value divided by a double
         *
         * @param dividend the dividend to divide by
         */
        constexpr void operator/=(double dividend) { value /= dividend; }

        /**
         * @brief set the value of this quantity to a double, only if the quantity is a number
         *
         * @param rhs the double to assign
         */
        constexpr void operator=(const double& rhs) {
            static_assert(std::ratio_equal<mass, std::ratio<0>>() && std::ratio_equal<length, std::ratio<0>>() &&
                              std::ratio_equal<time, std::ratio<0>>() && std::ratio_equal<current, std::ratio<0>>() &&
                              std::ratio_equal<angle, std::ratio<0>>() &&
                              std::ratio_equal<temperature, std::ratio<0>>() &&
                              std::ratio_equal<luminosity, std::ratio<0>>() && std::ratio_equal<moles, std::ratio<0>>(),
                          "Cannot assign a double directly to a non-number unit type");
            value = rhs;
        }
};

template <typename Q> struct LookupName {
        using Named = Q;
};

template <typename Q> using Named = typename LookupName<Q>::Named;

// quantity checker. Used by the isQuantity concept
template <typename Mass = std::ratio<0>, typename Length = std::ratio<0>, typename Time = std::ratio<0>,
          typename Current = std::ratio<0>, typename Angle = std::ratio<0>, typename Temperature = std::ratio<0>,
          typename Luminosity = std::ratio<0>, typename Moles = std::ratio<0>>
void quantityChecker(Quantity<Mass, Length, Time, Current, Angle, Temperature, Luminosity, Moles>) {}

// isQuantity concept
template <typename Q>
concept isQuantity = requires(Q q) { quantityChecker(q); };

// Isomorphic concept - used to ensure unit equivalency
template <typename Q, typename... Quantities>
concept Isomorphic = ((std::convertible_to<Q, Quantities> && std::convertible_to<Quantities, Q>) && ...);

// Un(type)safely coerce the a unit into a different unit
template <isQuantity Q1, isQuantity Q2> constexpr inline Q1 unit_cast(Q2 quantity) { return Q1(quantity.internal()); }

template <isQuantity Q1, isQuantity Q2> using Multiplied = Named<Quantity<
    std::ratio_add<typename Q1::mass, typename Q2::mass>, std::ratio_add<typename Q1::length, typename Q2::length>,
    std::ratio_add<typename Q1::time, typename Q2::time>, std::ratio_add<typename Q1::current, typename Q2::current>,
    std::ratio_add<typename Q1::angle, typename Q2::angle>,
    std::ratio_add<typename Q1::temperature, typename Q2::temperature>,
    std::ratio_add<typename Q1::luminosity, typename Q2::luminosity>,
    std::ratio_add<typename Q1::moles, typename Q2::moles>>>;

template <isQuantity Q1, isQuantity Q2> using Divided =
    Named<Quantity<std::ratio_subtract<typename Q1::mass, typename Q2::mass>,
                   std::ratio_subtract<typename Q1::length, typename Q2::length>,
                   std::ratio_subtract<typename Q1::time, typename Q2::time>,
                   std::ratio_subtract<typename Q1::current, typename Q2::current>,
                   std::ratio_subtract<typename Q1::angle, typename Q2::angle>,
                   std::ratio_subtract<typename Q1::temperature, typename Q2::temperature>,
                   std::ratio_subtract<typename Q1::luminosity, typename Q2::luminosity>,
                   std::ratio_subtract<typename Q1::moles, typename Q2::moles>>>;

template <isQuantity Q, typename factor> using Exponentiated = Named<
    Quantity<std::ratio_multiply<typename Q::mass, factor>, std::ratio_multiply<typename Q::length, factor>,
             std::ratio_multiply<typename Q::time, factor>, std::ratio_multiply<typename Q::current, factor>,
             std::ratio_multiply<typename Q::angle, factor>, std::ratio_multiply<typename Q::temperature, factor>,
             std::ratio_multiply<typename Q::luminosity, factor>, std::ratio_multiply<typename Q::moles, factor>>>;

template <isQuantity Q, typename quotient> using Rooted = Named<
    Quantity<std::ratio_divide<typename Q::mass, quotient>, std::ratio_divide<typename Q::length, quotient>,
             std::ratio_divide<typename Q::time, quotient>, std::ratio_divide<typename Q::current, quotient>,
             std::ratio_divide<typename Q::angle, quotient>, std::ratio_divide<typename Q::temperature, quotient>,
             std::ratio_divide<typename Q::luminosity, quotient>, std::ratio_divide<typename Q::moles, quotient>>>;

template <isQuantity Q> inline std::ostream& operator<<(std::ostream& os, const Q& quantity) {
    if constexpr (!std::is_same_v<Named<Q>, Q>) {
        os << Named<Q>(quantity);
    } else {
        os << quantity.internal();
        if constexpr (Q::mass::num != 0) {
            os << " kg^" << Q::mass::num;
            if constexpr (Q::mass::den != 1) os << "/" << Q::mass::den;
        }
        if constexpr (Q::length::num != 0) {
            os << "*m^" << Q::length::num;
            if constexpr (Q::length::den != 1) os << "/" << Q::length::den;
        }
        if constexpr (Q::time::num != 0) {
            os << "*s^" << Q::time::num;
            if constexpr (Q::time::den != 1) os << "/" << Q::time::den;
        }
        if constexpr (Q::current::num != 0) {
            os << "*A^" << Q::current::num;
            if constexpr (Q::current::den != 1) os << "/" << Q::current::den;
        }
        if constexpr (Q::angle::num != 0) {
            os << "*rad^" << Q::angle::num;
            if constexpr (Q::angle::den != 1) os << "/" << Q::angle::den;
        }
        if constexpr (Q::temperature::num != 0) {
            os << "*K^" << Q::temperature::num;
            if constexpr (Q::temperature::den != 1) os << "/" << Q::temperature::den;
        }
        if constexpr (Q::luminosity::num != 0) {
            os << "*cd^" << Q::luminosity::num;
            if constexpr (Q::luminosity::den != 1) os << "/" << Q::luminosity::den;
        }
        if constexpr (Q::moles::num != 0) {
            os << "*mol^" << Q::moles::num;
            if constexpr (Q::moles::den != 1) os << "/" << Q::moles::den;
        }
    }
    return os;
}

template <isQuantity Q, isQuantity R> constexpr Q operator+(Q lhs, R rhs)
    requires Isomorphic<Q, R>
{
    return Q(lhs.internal() + rhs.internal());
}

template <isQuantity Q, isQuantity R> constexpr Q operator-(Q lhs, R rhs)
    requires Isomorphic<Q, R>
{
    return Q(lhs.internal() - rhs.internal());
}

template <isQuantity Q> constexpr Q operator*(Q quantity, double multiple) { return Q(quantity.internal() * multiple); }

template <isQuantity Q> constexpr Q operator*(double multiple, Q quantity) { return Q(quantity.internal() * multiple); }

template <isQuantity Q> constexpr Q operator/(Q quantity, double divisor) { return Q(quantity.internal() / divisor); }

template <isQuantity Q1, isQuantity Q2, isQuantity Q3 = Multiplied<Q1, Q2>> Q3 constexpr operator*(Q1 lhs, Q2 rhs) {
    return Q3(lhs.internal() * rhs.internal());
}

template <isQuantity Q1, isQuantity Q2, isQuantity Q3 = Divided<Q1, Q2>> Q3 constexpr operator/(Q1 lhs, Q2 rhs) {
    return Q3(lhs.internal() / rhs.internal());
}

template <isQuantity Q, isQuantity R> constexpr bool operator==(const Q& lhs, const R& rhs)
    requires Isomorphic<Q, R>
{
    return (lhs.internal() == rhs.internal());
}

template <isQuantity Q, isQuantity R> constexpr bool operator!=(const Q& lhs, const R& rhs)
    requires Isomorphic<Q, R>
{
    return (lhs.internal() != rhs.internal());
}

template <isQuantity Q, isQuantity R> constexpr bool operator<=(const Q& lhs, const R& rhs)
    requires Isomorphic<Q, R>
{
    return (lhs.internal() <= rhs.internal());
}

template <isQuantity Q, isQuantity R> constexpr bool operator>=(const Q& lhs, const R& rhs)
    requires Isomorphic<Q, R>
{
    return (lhs.internal() >= rhs.internal());
}

template <isQuantity Q, isQuantity R> constexpr bool operator<(const Q& lhs, const R& rhs)
    requires Isomorphic<Q, R>
{
    return (lhs.internal() < rhs.internal());
}

template <isQuantity Q, isQuantity R> constexpr bool operator>(const Q& lhs, const R& rhs)
    requires Isomorphic<Q, R>
{
    return (lhs.internal() > rhs.internal());
}

#define NEW_UNIT(Name, Full, suffix, m, l, t, i, a, o, j, n)                                                           \
    class Name : public Quantity<std::ratio<m>, std::ratio<l>, std::ratio<t>, std::ratio<i>, std::ratio<a>,            \
                                 std::ratio<o>, std::ratio<j>, std::ratio<n>> {                                        \
        public:                                                                                                        \
            explicit constexpr Name(double value)                                                                      \
                : Quantity<std::ratio<m>, std::ratio<l>, std::ratio<t>, std::ratio<i>, std::ratio<a>, std::ratio<o>,   \
                           std::ratio<j>, std::ratio<n>>(value) {}                                                     \
            constexpr Name(Quantity<std::ratio<m>, std::ratio<l>, std::ratio<t>, std::ratio<i>, std::ratio<a>,         \
                                    std::ratio<o>, std::ratio<j>, std::ratio<n>>                                       \
                               value)                                                                                  \
                : Quantity<std::ratio<m>, std::ratio<l>, std::ratio<t>, std::ratio<i>, std::ratio<a>, std::ratio<o>,   \
                           std::ratio<j>, std::ratio<n>>(value) {};                                                    \
    };                                                                                                                 \
    template <> struct LookupName<Quantity<std::ratio<m>, std::ratio<l>, std::ratio<t>, std::ratio<i>, std::ratio<a>,  \
                                           std::ratio<o>, std::ratio<j>, std::ratio<n>>> {                             \
            using Named = Name;                                                                                        \
    };                                                                                                                 \
    [[maybe_unused]] constexpr Name Full = Name(1.0);                                                                  \
    constexpr Name operator""_##suffix(long double value) {                                                            \
        return Name(Quantity<std::ratio<m>, std::ratio<l>, std::ratio<t>, std::ratio<i>, std::ratio<a>, std::ratio<o>, \
                             std::ratio<j>, std::ratio<n>>(static_cast<double>(value)));                               \
    }                                                                                                                  \
    constexpr Name operator""_##suffix(unsigned long long value) {                                                     \
        return Name(Quantity<std::ratio<m>, std::ratio<l>, std::ratio<t>, std::ratio<i>, std::ratio<a>, std::ratio<o>, \
                             std::ratio<j>, std::ratio<n>>(static_cast<double>(value)));                               \
    }                                                                                                                  \
    inline std::ostream& operator<<(std::ostream& os, const Name& quantity) {                                          \
        os << quantity.internal() << " " << #Full;                                                                     \
        return os;                                                                                                     \
    }                                                                                                                  \
    constexpr inline Name from_##suffix(double value) { return Name(value); }                                          \
    constexpr inline double to_##suffix(Name quantity) { return quantity.internal(); }

#define NEW_UNIT_LITERAL(Name, Full, suffix, multiple)                                                                 \
    [[maybe_unused]] constexpr Name Full = multiple;                                                                   \
    constexpr Name operator""_##suffix(long double value) { return static_cast<double>(value) * multiple; }            \
    constexpr Name operator""_##suffix(unsigned long long value) { return static_cast<double>(value) * multiple; }     \
    constexpr inline Name from_##suffix(double value) { return value * multiple; }                                     \
    constexpr inline double to_##suffix(Name quantity) { return quantity.convert(multiple); }

#define NEW_METRIC_PREFIXES(Name, Full, base)                                                                          \
    NEW_UNIT_LITERAL(Name, Tera##Full, T##base, base * 1E12)                                                           \
    NEW_UNIT_LITERAL(Name, Giga##Full, G##base, base * 1E9)                                                            \
    NEW_UNIT_LITERAL(Name, Mega##Full, M##base, base * 1E6)                                                            \
    NEW_UNIT_LITERAL(Name, Kilo##Full, k##base, base * 1E3)                                                            \
    NEW_UNIT_LITERAL(Name, Centi##Full, c##base, base / 1E2)                                                           \
    NEW_UNIT_LITERAL(Name, Milli##Full, m##base, base / 1E3)                                                           \
    NEW_UNIT_LITERAL(Name, Micro##Full, u##base, base / 1E6)                                                           \
    NEW_UNIT_LITERAL(Name, Nano##Full, n##base, base / 1E9)

NEW_UNIT(Number, One, num, 0, 0, 0, 0, 0, 0, 0, 0)
NEW_UNIT_LITERAL(Number, Percent, percent, One / 100.0);

NEW_UNIT(Mass, Kilogram, kg, 1, 0, 0, 0, 0, 0, 0, 0)
NEW_UNIT_LITERAL(Mass, Gram, g, Kilogram / 1000)
NEW_UNIT_LITERAL(Mass, Pound, lb, Gram * 453.6)

NEW_UNIT(Time, Second, sec, 0, 0, 1, 0, 0, 0, 0, 0)
NEW_METRIC_PREFIXES(Time, second, Second)
NEW_UNIT_LITERAL(Time, Minute, min, Second * 60)
NEW_UNIT_LITERAL(Time, Hour, hr, Minute * 60)
NEW_UNIT_LITERAL(Time, Day, day, Hour * 24)

NEW_UNIT(Length, Meter, m, 0, 1, 0, 0, 0, 0, 0, 0)
NEW_METRIC_PREFIXES(Length, meter, Meter)
NEW_UNIT_LITERAL(Length, Inch, in, Centimeter * 2.54)
NEW_UNIT_LITERAL(Length, Foot, ft, Inch * 12)
NEW_UNIT_LITERAL(Length, Yard, yd, Foot * 3)
NEW_UNIT_LITERAL(Length, Mile, mi, Foot * 5280)
NEW_UNIT_LITERAL(Length, Tile, tile, Millimeter * 600)

NEW_UNIT(Area, MeterSquared, m2, 0, 2, 0, 0, 0, 0, 0, 0)
NEW_UNIT_LITERAL(Area, TerameterSquared, Tm2, Terameter* Terameter);
NEW_UNIT_LITERAL(Area, GigameterSquared, Gm2, Gigameter * Gigameter);
NEW_UNIT_LITERAL(Area, MegameterSquared, Mm2, Megameter * Megameter);
NEW_UNIT_LITERAL(Area, KilometerSquared, km2, Kilometer * Kilometer);
NEW_UNIT_LITERAL(Area, CentimeterSquared, cm2, Centimeter * Centimeter);
NEW_UNIT_LITERAL(Area, MillimeterSquared, mm2, Millimeter * Millimeter);
NEW_UNIT_LITERAL(Area, MicrometerSquared, um2, Micrometer * Micrometer);
NEW_UNIT_LITERAL(Area, NanometerSquared, nm2, Nanometer * Nanometer);
NEW_UNIT_LITERAL(Area, InchSquared, in2, Inch * Inch);

NEW_UNIT(LinearVelocity, MetersPerSecond, mps, 0, 1, -1, 0, 0, 0, 0, 0)
NEW_METRIC_PREFIXES(LinearVelocity, metersPerSecond, MetersPerSecond);
NEW_UNIT_LITERAL(LinearVelocity, MetersPerHour, mph, Meter / Hour)
NEW_METRIC_PREFIXES(LinearVelocity, metersPerHour, MetersPerHour)
NEW_UNIT_LITERAL(LinearVelocity, InchesPerSecond, inps, Inch / Second)
NEW_UNIT_LITERAL(LinearVelocity, MilesPerHour, miph, Mile / Hour)

NEW_UNIT(LinearAcceleration, MetersPerSecondSquared, mps2, 0, 1, -2, 0, 0, 0, 0, 0)
NEW_METRIC_PREFIXES(LinearAcceleration, metersPerSecondSquared, MetersPerSecondSquared)
NEW_UNIT_LITERAL(LinearAcceleration, MetersPerHourSquared, mph2, Meter / (Hour * Hour))
NEW_METRIC_PREFIXES(LinearAcceleration, metersPerHourSquared, MetersPerHourSquared)
NEW_UNIT_LITERAL(LinearAcceleration, InchesPerSecondSquared, inps2, Inch / (Second * Second))
NEW_UNIT_LITERAL(LinearAcceleration, MilesPerHourSquared, miph2, Mile / (Hour * Hour))

NEW_UNIT(LinearJerk, MetersPerSecondCubed, mps3, 0, 1, -3, 0, 0, 0, 0, 0)
NEW_METRIC_PREFIXES(LinearJerk, metersPerSecondCubed, MetersPerSecondCubed)
NEW_UNIT_LITERAL(LinearJerk, MetersPerHourCubed, mph3, Meter / (Hour * Hour * Hour))
NEW_METRIC_PREFIXES(LinearJerk, metersPerHourCubed, MetersPerHourCubed)
NEW_UNIT_LITERAL(LinearJerk, InchesPerSecondCubed, inps3, Inch / (Second * Second * Second))
NEW_UNIT_LITERAL(LinearJerk, MilesPerHourCubed, miph3, Mile / (Hour * Hour * Hour))

NEW_UNIT(Curvature, RadiansPerMeter, radpm, 0, -1, 0, 0, 0, 0, 0, 0);

NEW_UNIT(Inertia, KilogramMeterSquared, kgm2, 1, 2, 0, 0, 0, 0, 0, 0)

NEW_UNIT(Force, Newton, N, 1, 1, -2, 0, 0, 0, 0, 0)

NEW_UNIT(Torque, NewtonMeter, Nm, 1, 2, -2, 0, 0, 0, 0, 0)

NEW_UNIT(Power, Watt, watt, 1, 2, -3, 0, 0, 0, 0, 0)

NEW_UNIT(Current, Ampere, amp, 0, 0, 0, 1, 0, 0, 0, 0)

NEW_UNIT(Charge, Coulomb, coulomb, 0, 0, 1, 1, 0, 0, 0, 0)

NEW_UNIT(Voltage, Volt, volt, 1, 2, -3, -1, 0, 0, 0, 0)
NEW_METRIC_PREFIXES(Voltage, volt, Volt);

NEW_UNIT(Resistance, Ohm, ohm, 1, 2, -3, -2, 0, 0, 0, 0)
NEW_METRIC_PREFIXES(Resistance, ohm, Ohm)

NEW_UNIT(Conductance, Seimen, siemen, -1, -2, 3, 2, 0, 0, 0, 0)
NEW_METRIC_PREFIXES(Conductance, siemen, Seimen);

NEW_UNIT(Luminosity, Candela, candela, 0, 0, 0, 0, 0, 0, 1, 0);

NEW_UNIT(Moles, Mol, mol, 0, 0, 0, 0, 0, 0, 0, 1);

namespace units {
template <isQuantity Q> constexpr Q abs(const Q& lhs) { return Q(std::abs(lhs.internal())); }

template <isQuantity Q, isQuantity R> constexpr Q max(const Q& lhs, const R& rhs)
    requires Isomorphic<Q, R>
{
    return (lhs > rhs ? lhs : rhs);
}

template <isQuantity Q, isQuantity R> constexpr Q min(const Q& lhs, const R& rhs)
    requires Isomorphic<Q, R>
{
    return (lhs < rhs ? lhs : rhs);
}

template <int R, isQuantity Q, isQuantity S = Exponentiated<Q, std::ratio<R>>> constexpr S pow(const Q& lhs) {
    return S(std::pow(lhs.internal(), R));
}

template <isQuantity Q, isQuantity S = Exponentiated<Q, std::ratio<2>>> constexpr S square(const Q& lhs) {
    return pow<2>(lhs);
}

template <isQuantity Q, isQuantity S = Exponentiated<Q, std::ratio<3>>> constexpr S cube(const Q& lhs) {
    return pow<3>(lhs);
}

template <int R, isQuantity Q, isQuantity S = Rooted<Q, std::ratio<R>>> constexpr S root(const Q& lhs) {
    return S(std::pow(lhs.internal(), 1.0 / R));
}

template <isQuantity Q, isQuantity S = Rooted<Q, std::ratio<2>>> constexpr S sqrt(const Q& lhs) { return root<2>(lhs); }

template <isQuantity Q, isQuantity S = Rooted<Q, std::ratio<3>>> constexpr S cbrt(const Q& lhs) { return root<3>(lhs); }

template <isQuantity Q, isQuantity R> constexpr Q hypot(const Q& lhs, const R& rhs)
    requires Isomorphic<Q, R>
{
    return Q(std::hypot(lhs.internal(), rhs.internal()));
}

template <isQuantity Q, isQuantity R> constexpr Q mod(const Q& lhs, const R& rhs)
    requires Isomorphic<Q, R>
{
    return Q(std::fmod(lhs.internal(), rhs.internal()));
}

template <isQuantity Q1, isQuantity Q2> constexpr Q1 copysign(const Q1& lhs, const Q2& rhs) {
    return Q1(std::copysign(lhs.internal(), rhs.internal()));
}

template <isQuantity Q> constexpr int sgn(const Q& lhs) { return lhs.internal() < 0 ? -1 : 1; }

template <isQuantity Q> constexpr bool signbit(const Q& lhs) { return std::signbit(lhs.internal()); }

template <isQuantity Q, isQuantity R, isQuantity S> constexpr Q clamp(const Q& lhs, const R& lo, const S& hi)
    requires Isomorphic<Q, R, S>
{
    return Q(std::clamp(lhs.internal(), lo.internal(), hi.internal()));
}

template <isQuantity Q, isQuantity R> constexpr Q ceil(const Q& lhs, const R& rhs)
    requires Isomorphic<Q, R>
{
    return Q(std::ceil(lhs.internal() / rhs.internal()) * rhs.internal());
}

template <isQuantity Q, isQuantity R> constexpr Q floor(const Q& lhs, const R& rhs)
    requires Isomorphic<Q, R>
{
    return Q(std::floor(lhs.internal() / rhs.internal()) * rhs.internal());
}

template <isQuantity Q, isQuantity R> constexpr Q trunc(const Q& lhs, const R& rhs)
    requires Isomorphic<Q, R>
{
    return Q(std::trunc(lhs.internal() / rhs.internal()) * rhs.internal());
}

template <isQuantity Q, isQuantity R> constexpr Q round(const Q& lhs, const R& rhs)
    requires Isomorphic<Q, R>
{
    return Q(std::round(lhs.internal() / rhs.internal()) * rhs.internal());
}
} // namespace units

// Convert an angular unit `Q` to a linear unit correctly;
// mostly useful for velocities
template <isQuantity Q> Quantity<typename Q::mass, typename Q::angle, typename Q::time, typename Q::current,
                                 typename Q::length, typename Q::temperature, typename Q::luminosity, typename Q::moles>
toLinear(Quantity<typename Q::mass, typename Q::length, typename Q::time, typename Q::current, typename Q::angle,
                  typename Q::temperature, typename Q::luminosity, typename Q::moles>
             angular,
         Length diameter) {
    return unit_cast<Quantity<typename Q::mass, typename Q::angle, typename Q::time, typename Q::current,
                              typename Q::length, typename Q::temperature, typename Q::luminosity, typename Q::moles>>(
        angular * (diameter / 2.0));
}

// Convert an linear unit `Q` to a angular unit correctly;
// mostly useful for velocities
template <isQuantity Q> Quantity<typename Q::mass, typename Q::angle, typename Q::time, typename Q::current,
                                 typename Q::length, typename Q::temperature, typename Q::luminosity, typename Q::moles>
toAngular(Quantity<typename Q::mass, typename Q::length, typename Q::time, typename Q::current, typename Q::angle,
                   typename Q::temperature, typename Q::luminosity, typename Q::moles>
              linear,
          Length diameter) {
    return unit_cast<Quantity<typename Q::mass, typename Q::angle, typename Q::time, typename Q::current,
                              typename Q::length, typename Q::temperature, typename Q::luminosity, typename Q::moles>>(
        linear / (diameter / 2.0));
}
