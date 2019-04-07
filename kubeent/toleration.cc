#include "kubeent/toleration.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char TOLERATION_EFFECT[] = "effect";
char TOLERATION_KEY[] = "key";
char TOLERATION_OPERATOR[] = "operator";
char TOLERATION_TOLERATION_SECONDS[] = "tolerationSeconds";
char TOLERATION_VALUE[] = "value";

void toleration::serialize(toleration & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.effect)
        .add(obj.key)
        .add(obj.operator_)
        .add(obj.toleration_seconds)
        .add(obj.value)
        .serialize(str);
}

}
}
