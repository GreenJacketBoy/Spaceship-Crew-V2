#ifndef AT_INDEX_HPP
#define AT_INDEX_HPP

#include <cstddef>
#include <optional>
#include <set>
#include <type_traits>

template<typename T> 
concept Numeric = std::is_arithmetic_v<T>;

namespace util {
    template<typename T, Numeric Size> 
    inline const std::optional<const T*> atIndex(const std::set<T> &set, Size index) {
        Size i = 0;
        for (const auto &item: set) {
            if (index == i) return std::optional<const T*>(&item);
            i++;
        }
        return std::optional<const T*>();
    }
}

#endif // !AT_INDEX_HPPGET_ROOM_HPP
