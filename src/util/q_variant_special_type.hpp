#ifndef Q_VARIANT_SPECIAL_TYPE_HPP
#define Q_VARIANT_SPECIAL_TYPE_HPP

#include <cstddef>
#include <qvariant.h>

namespace util {

    /** Because QVariant doesn't have a constructor for all types */
    template <typename T>
    inline constexpr QVariant QVariantSpecialType(const T specialTypeVariable) {
        QVariant qVariant;
        qVariant.setValue(specialTypeVariable);
        return qVariant;
    }

    inline constexpr QVariant qVariantSizeT(const size_t number) {
        return util::QVariantSpecialType<size_t>(number);
    }
}

#endif // !Q_VARIANT_SPECIAL_TYPE_HPP
