#include "kubeent/stateful_set_update_strategy.hpp"

namespace navagraha {
namespace kubeent {

char STATEFUL_SET_UPDATE_STRATEGY_ROLLING_UPDATE[] = "rollingUpdate";
char STATEFUL_SET_UPDATE_STRATEGY_TYPE[] = "type";

void stateful_set_update_strategy::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->rolling_update)
        .add(this->type);
}

}
}
