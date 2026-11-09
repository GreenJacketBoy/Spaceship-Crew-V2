#ifndef NUMERIC_CONCEPT_HPP
#define NUMERIC_CONCEPT_HPP

#include <type_traits>

namespace util {
    template<typename T> 
    concept Numeric = std::is_arithmetic_v<T>;
}

#endif // !NUMERIC_CONCEPT_HPP
