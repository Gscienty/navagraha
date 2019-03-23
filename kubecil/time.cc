#include "kubecil/time.hpp"
#include <list>
#include <functional>
#include <algorithm>

namespace navagraha {
namespace kubecil {

char TIME_FIELD_EFFECT[] = "effect";
char TIME_FIELD_KEY[] = "key";
char TIME_FIELD_TOLERATION_SECONDS[] = "tolerationSeconds";
char TIME_FIELD_VALUE[] = "value";

void time::serialize(time & obj, std::ostringstream & str)
{
    std::list<std::pair<bool, std::function<void (std::ostringstream &)>>> serializers = {
        extensions::field_serializer(obj.effect),
        extensions::field_serializer(obj.key),
        extensions::field_serializer(obj.toleration_seconds),
        extensions::field_serializer(obj.value)
    };

    str.put('{');
    extensions::fields_serialize(serializers, str);
    str.put('}');
}

}
}
