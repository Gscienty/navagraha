#include "kubeent/lifecycle.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char LIFECYCLE_POST_START[] = "postStart";
char LIFECYCLE_PRE_STOP[] = "preStop";

void serialize(lifecycle & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.post_start)
        .add(obj.pre_stop)
        .serialize(str);
}

}
}
