#include "kubeent/deployment_strategy.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char DEPLOYMENT_STRATEGY_ROLLING_UPDATE[] = "rollingUpdate";
char DEPLOYMENT_STRATEGY_TYPE[] = "type";

void deployment_strategy::serialize(deployment_strategy & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.rolling_update)
        .add(obj.type)
        .serialize(str);
}

}
}
