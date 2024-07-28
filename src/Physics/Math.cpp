#include "Math.h"
#include <random>
#include <type_traits>

template <typename T>
T randomNumber(T min, T max) {
    static_assert(std::is_arithmetic<T>::value, "Template parameter must be a numeric type");

    // Random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    if constexpr (std::is_integral<T>::value) {
        std::uniform_int_distribution<T> dis(min, max);
        return dis(gen);
    } else {
        std::uniform_real_distribution<T> dis(min, max);
        return dis(gen);
    }
}

