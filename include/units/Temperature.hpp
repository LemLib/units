#pragma once

#include "units/units.hpp"

using Temperature = Quantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>,
                             std::ratio<0>, std::ratio<0>>;

constexpr Temperature kelvin = Temperature(1.0);
constexpr Temperature celcius = Temperature();
constexpr Temperature farenheight = Temperature();

constexpr Temperature operator""_kelvin(long double value) { return static_cast<double>(value) * kelvin; }

constexpr Temperature operator""_kelvin(unsigned long long value) { return static_cast<double>(value) * kelvin; }

constexpr Temperature operator""_celcius(long double value) { return (static_cast<double>(value) + 273.15) * kelvin; }

constexpr Temperature operator""_celcius(unsigned long long value) {
    return (static_cast<double>(value) + 273.15) * kelvin;
}

constexpr Temperature operator""_farenheight(long double value) {
    return ((static_cast<double>(value) - 32) * (5.0 / 9.0) + 273.5) * kelvin;
}

constexpr Temperature operator""_farenheight(unsigned long long value) {
    return ((static_cast<double>(value) - 32) * (5.0 / 9.0) + 273.5) * kelvin;
}

namespace units {

constexpr inline Temperature from_kelvin(double value) { return Temperature(value); }

constexpr inline double to_kelvin(Temperature quantity) { return quantity.val(); }

constexpr inline Temperature from_celcius(double value) { return Temperature(value + 273.15); }

constexpr inline double to_celcius(Temperature quantity) { return quantity.val() - 273.15; }

constexpr inline Temperature from_farenheight(double value) { return (value - 32) * (5.0 / 9.0) + 273.15; }

constexpr inline double to_farenheight(Temperature quantity) { return (quantity.val() - 273.15) * (9.0 / 5.0) + 32; }

} // namespace units