#include "kubeent/deployment_strategy.hpp"

namespace navagraha {
namespace kubeent {

char DEPLOYMENT_STRATEGY_ROLLING_UPDATE[] = "rollingUpdate";
char DEPLOYMENT_STRATEGY_TYPE[] = "type";

void deployment_strategy::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->rolling_update)
        .add(this->type);
}

}
}
