#include "kubeent/time.hpp"

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

}
}
