#ifndef AT_INDEX_HPP
#define AT_INDEX_HPP

#include "numeric_concept.hpp"
#include <map>
#include <memory>
#include <optional>
#include <set>

namespace util {
    template<typename T, util::Numeric Size> 
    inline const std::optional<const T*> atIndex(const std::set<T> &set, Size index) {
        Size i = 0;
        for (const auto &item: set) {
            if (index == i) return std::addressof(item);
            i++;
        }
        return std::nullopt; // OOOOH MAGAWD
    }

    template<typename Key, typename Value, util::Numeric Size> 
    inline const std::optional<const Value*> atIndex(const std::map<Key, Value> &map, Size index) {
        Size i = 0;
        for (const auto &[_, item]: map) {
            if (index == i) return std::addressof(item);
            i++;
        }
        return std::nullopt;
    }

    template<typename Key, typename Value, util::Numeric Size> 
    inline const std::optional<const Key*> atIndexKey(const std::map<Key, Value> &map, Size index) {
        Size i = 0;
        for (const auto &[key, _]: map) {
            if (index == i) return std::addressof(key);
            i++;
        }
        return std::nullopt;
    }
}

#endif // !AT_INDEX_HPPGET_ROOM_HPP
