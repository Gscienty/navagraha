#include "kubeent/rolling_update_deployment.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char ROLLING_UPDATE_DEPLOYMENT_MAX_SURGE[] = "maxSurge";
char ROLLING_UPDATE_DEPLOYMENT_MAX_UNAVAILABLE[] = "maxUnavailable";

void rolling_update_deployment::serialize(rolling_update_deployment & obj,
                                          std::ostringstream & str)
{
    extensions::link_serializer(extensions::link_serializer_type::object)
        .add(obj.max_surge)
        .add(obj.max_unavailable)
        .serialize(str);
}

}
}
