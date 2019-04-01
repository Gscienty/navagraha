#include "kubeent/time.hpp"
#include <list>
#include <functional>
#include <algorithm>
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char TIME_FIELD_EFFECT[] = "effect";
char TIME_FIELD_KEY[] = "key";
char TIME_FIELD_TOLERATION_SECONDS[] = "tolerationSeconds";
char TIME_FIELD_VALUE[] = "value";

void time::serialize(time & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.effect)
        .add(obj.key)
        .add(obj.toleration_seconds)
        .add(obj.value)
        .serialize(str);
}

}
}
