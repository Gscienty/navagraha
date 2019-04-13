#include "kubeent/rolling_update_daemon_set.hpp"

namespace navagraha {
namespace kubeent {

char ROLLING_UPDATE_DAEMON_SET_MAX_UNAVAILABLE[] = "maxUnavailable";

void rolling_update_daemon_set::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->max_unavailable);
}

}
}
