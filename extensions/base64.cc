#include "extensions/base64.hpp"
#include <sstream>
#include <algorithm>

#include <iostream>

namespace navagraha {
namespace extensions {

char BASE64_ALPHA[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    '+', '/'
};

template <int T_Off> struct first_byte_mask {
    constexpr static const int value = 0xFC >> T_Off;
};

template <int T_Off> struct second_byte_mask {
    constexpr static const int value = T_Off < 3 ? 0 : 0xFF - ((0x01 << (10 - T_Off)) - 1);
};

template <int T_Off> struct next_off {
    constexpr static const int value = (6 + T_Off) % 8;
};

template <int T_Off> struct next_idx_operand {
    constexpr static const int value = T_Off < 2 ? 0 : 1;
};

template <int T_Off> static inline int base64_calculator(unsigned char b, unsigned char nb)
{
    if (T_Off <= 3) {
        return (first_byte_mask<T_Off>::value & b) >> (2 - T_Off);
    }
    else {
        return ((first_byte_mask<T_Off>::value & b) << (T_Off - 2)) | ((second_byte_mask<T_Off>::value & nb) >> (10 - T_Off));
    }
}

static inline unsigned char __val_nth(std::string & val, size_t i) {
    return i < val.size() ? val[i] : 0;
}

static inline size_t __size(size_t n)
{
    return (n + (3 - n % 3) % 3) / 3 * 4 - (3 - n % 3) % 3;
}

static inline size_t __extend_size(size_t n)
{
    return (3 - n % 3) % 3;
}

#define BASE64_ENCODE_OFF_CASE(_str, _val, _i, _off, _off_val) \
    case (_off_val): \
        (_str).put(BASE64_ALPHA[base64_calculator<(_off_val)>(__val_nth((_val), (_i)), __val_nth((_val), (_i) + 1))]); \
        (_off) = next_off<(_off_val)>::value; \
        (_i) += next_idx_operand<(_off_val)>::value; \
        break

std::string base64_encode(std::string val)
{
    std::ostringstream str;
    int byte_off = 0;
    int val_off = 0;
    size_t size = __size(val.size());
    size_t extend_size = __extend_size(val.size());

    for (size_t i = 0; i < size; i++) {
        switch (byte_off) {
            BASE64_ENCODE_OFF_CASE(str, val, val_off, byte_off, 0);
            BASE64_ENCODE_OFF_CASE(str, val, val_off, byte_off, 2);
            BASE64_ENCODE_OFF_CASE(str, val, val_off, byte_off, 4);
            BASE64_ENCODE_OFF_CASE(str, val, val_off, byte_off, 6);
        }
    }

    while (extend_size--) {
        str.put('=');
    }

    return str.str();
}

}
}
