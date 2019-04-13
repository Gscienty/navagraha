#include "kubeent/rolling_update_stateful_set_strategy.hpp"

namespace navagraha {
namespace kubeent {

char ROLLING_UPDATE_STATEFUL_SET_STRATEGY_PARTITION[] = "partition";

void rolling_update_stateful_set_strategy::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->partition);
}

}
}
