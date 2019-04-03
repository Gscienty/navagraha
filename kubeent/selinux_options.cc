#include "kubeent/selinux_options.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

void selinux_options::serialize(selinux_options & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.level)
        .add(obj.role)
        .add(obj.type)
        .add(obj.user)
        .serialize(str);
}
}
}
