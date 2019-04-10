#include "kubeent/toleration.hpp"

namespace navagraha {
namespace kubeent {

char TOLERATION_EFFECT[] = "effect";
char TOLERATION_KEY[] = "key";
char TOLERATION_OPERATOR[] = "operator";
char TOLERATION_TOLERATION_SECONDS[] = "tolerationSeconds";
char TOLERATION_VALUE[] = "value";

void toleration::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->effect)
        .add(this->key)
        .add(this->operator_)
        .add(this->toleration_seconds)
        .add(this->value);
}

}
}
