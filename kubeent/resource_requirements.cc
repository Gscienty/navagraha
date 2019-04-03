#include "kubeent/resource_requirements.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char RESOURCE_REQUIREMENTS_LIMITS[] = "limits";
char RESOURCE_REQUIREMENTS_REQUESTS[] = "requests";

void serialize(resource_requirements & obj,
               std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.limits)
        .add(obj.requests)
        .serialize(str);
}
}
}
