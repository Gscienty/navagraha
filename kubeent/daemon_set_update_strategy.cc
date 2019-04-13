#include "kubeent/daemon_set_update_strategy.hpp"

namespace navagraha {
namespace kubeent {

char DAEMON_SET_UPDATE_STRATEGY_ROLLING_UPDATE[] = "rollingUpdate";
char DAEMON_SET_UPDATE_STRATEGY_TYPE[] = "type";

void daemon_set_update_strategy::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->rolling_update)
        .add(this->type);
}

}
}
