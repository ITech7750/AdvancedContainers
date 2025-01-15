#ifndef LABA3_HASHUTIL_H
#define LABA3_HASHUTIL_H

#include <string>
#include <type_traits>
#include "../../../../collectionunqptr/dinamicarray/DynamicArray.h"

class HashUtil {
private:
    static constexpr size_t P = 31;
    static constexpr size_t MOD = 1000000007;

    static size_t hashString(const std::string& str) {
        size_t hash = 0;
        size_t power = 1;
        for (char c : str) {
            hash = (hash + (c - 'a' + 1) * power) % MOD;
            power = (power * P) % MOD;
        }
        return hash;
    }

    template <typename T>
    static size_t hashNumber(const T& value) {
        static_assert(std::is_arithmetic<T>::value, "T must be a number");
        return static_cast<size_t>(value) % MOD;
    }

    template <typename T>
    static size_t hashContainer(const DynamicArray<T>& container) {
        size_t hash = 0;
        for (size_t i = 0; i < container.size(); ++i) {
            hash = (hash * P + hashValue(container.get(i))) % MOD;
        }
        return hash;
    }

public:
    template <typename T>
    static size_t hashValue(const T& value) {
        if constexpr (std::is_integral<T>::value || std::is_floating_point<T>::value) {
            return hashNumber(value);
        } else if constexpr (std::is_same<T, std::string>::value) {
            return hashString(value);
        } else if constexpr (std::is_same<T, DynamicArray<typename T::value_type>>::value) {
            return hashContainer(value);
        } else if constexpr (std::is_class<T>::value) {
            return std::hash<T>()(value);
        } else {
            static_assert(!std::is_same<T, T>::value, "Unsupported type for hashing");
        }
    }
};

#endif // LABA3_HASHUTIL_H
