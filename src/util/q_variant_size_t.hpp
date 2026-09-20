#ifndef Q_VARIANT_SIZE_T_HPP
#define Q_VARIANT_SIZE_T_HPP

#include <qvariant.h>

namespace util {

    /** Because QVariant doesn't have a constructor for size_t */
    constexpr QVariant qVariantSizeT(const size_t number) {
        QVariant qVariant;
        qVariant.setValue(number);
        return qVariant;
    }
}

#endif // !Q_VARIANT_SIZE_T_HPP
