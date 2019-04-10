#include "kubeent/rolling_update_deployment.hpp"

namespace navagraha {
namespace kubeent {

char ROLLING_UPDATE_DEPLOYMENT_MAX_SURGE[] = "maxSurge";
char ROLLING_UPDATE_DEPLOYMENT_MAX_UNAVAILABLE[] = "maxUnavailable";

void rolling_update_deployment::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->max_surge)
        .add(this->max_unavailable);
}

}
}
