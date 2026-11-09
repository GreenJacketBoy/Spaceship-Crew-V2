#ifndef INDEX_OF_HPP
#define INDEX_OF_HPP

#include "numeric_concept.hpp"
#include <map>
#include <optional>
#include <set>

namespace util {
    template<util::Numeric Size, typename T> 
    inline std::optional<Size> indexOf(const std::set<T> &set, const T &value) {
        Size index = 0;
        for (const auto &item: set) {
            if (value == item) return index;
            index++;
        }
        return std::nullopt;
    }

    template<util::Numeric Size, typename Key, typename Value> 
    inline std::optional<Size> indexOf(const std::map<Key, Value> &map, const Key key) {
        Size index = 0;
        for (const auto &[item, _]: map) {
            if (key == item) return index;
            index++;
        }
        return std::nullopt;
    }
}

#endif // !INDEX_OF_HPP
