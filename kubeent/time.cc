#include "kubeent/time.hpp"
#include "extensions/field.hpp"
#include <iostream>

namespace navagraha {
namespace kubeent {

char TIME_FIELD_EFFECT[] = "effect";
char TIME_FIELD_KEY[] = "key";
char TIME_FIELD_TOLERATION_SECONDS[] = "tolerationSeconds";
char TIME_FIELD_VALUE[] = "value";

void time::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->effect)
        .add(this->key)
        .add(this->toleration_seconds)
        .add(this->value);
}

time & time::deserialize(std::istringstream & str)
{
    while (str.peek() != '"'
           && (str.peek() < 'a' || 'z' < str.peek())
           && str.peek() != '{'
           && str.peek() != '['
           && (str.peek() < '0' || '9' < str.peek())) {
        str.get();
    }

    switch (str.peek()) {
    case '"':
        extensions::serializer<std::string>::deserialize(this->value.get(), str);
        break;
    case '{':
        extensions::serializer<extensions::serializable<time>>::deserialize(*this, str);
        break;
    }

    return *this;
}

}
}
