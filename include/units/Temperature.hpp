#pragma once

#include "units/units.hpp"

class Temperature : public Quantity<ratio<0>, ratio<0>, ratio<0>, ratio<0>, ratio<0>,
                                    ratio<1>, ratio<0>, ratio<0>> {
    public:
        explicit constexpr Temperature(double value)
            : Quantity<ratio<0>, ratio<0>, ratio<0>, ratio<0>, ratio<0>, ratio<1>,
                       ratio<0>, ratio<0>>(value) {}

        constexpr Temperature(Quantity<ratio<0>, ratio<0>, ratio<0>, ratio<0>, ratio<0>,
                                       ratio<1>, ratio<0>, ratio<0>>
                                  value)
            : Quantity<ratio<0>, ratio<0>, ratio<0>, ratio<0>, ratio<0>, ratio<1>,
                       ratio<0>, ratio<0>>(value) {};
};

template <> struct LookupName<Quantity<ratio<0>, ratio<0>, ratio<0>, ratio<0>, ratio<0>,
                                       ratio<1>, ratio<0>, ratio<0>>> {
        using Named = Temperature;
};

inline std::ostream& operator<<(std::ostream& os, const Temperature& quantity) {
    os << quantity.internal() << " k";
    return os;
}

constexpr Temperature kelvin = Temperature(1.0);

constexpr Temperature operator""_kelvin(long double value) { return Temperature(static_cast<double>(value)); }

constexpr Temperature operator""_kelvin(unsigned long long value) { return Temperature(static_cast<double>(value)); }

constexpr Temperature operator""_celsius(long double value) { return Temperature(static_cast<double>(value) + 273.15); }

constexpr Temperature operator""_celsius(unsigned long long value) {
    return Temperature(static_cast<double>(value) + 273.15);
}

constexpr Temperature operator""_fahrenheit(long double value) {
    return Temperature((static_cast<double>(value) - 32) * (5.0 / 9.0) + 273.5);
}

constexpr Temperature operator""_fahrenheit(unsigned long long value) {
    return Temperature((static_cast<double>(value) - 32) * (5.0 / 9.0) + 273.5);
}

namespace units {

constexpr inline Temperature from_kelvin(double value) { return Temperature(value); }

constexpr inline double to_kelvin(Temperature quantity) { return quantity.internal(); }

constexpr inline Temperature from_celsius(double value) { return Temperature(value + 273.15); }

constexpr inline double to_celsius(Temperature quantity) { return quantity.internal() - 273.15; }

constexpr inline Temperature from_fahrenheit(double value) { return Temperature((value - 32) * (5.0 / 9.0) + 273.15); }

constexpr inline double to_fahrenheit(Temperature quantity) {
    return (quantity.internal() - 273.15) * (9.0 / 5.0) + 32;
}

} // namespace units