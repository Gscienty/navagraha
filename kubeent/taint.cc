#include "kubeent/taint.hpp"

namespace navagraha {
namespace kubeent {

char TAINT_EFFECT[] = "effect";
char TAINT_KEY[] = "key";
char TAINT_TIME_ADDED[] = "timeAdded";
char TAINT_VALUE[] = "value";

void taint::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->effect)
        .add(this->key)
        .add(this->time_added)
        .add(this->value);
}

}
}
