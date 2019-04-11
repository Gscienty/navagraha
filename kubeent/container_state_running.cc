#include "kubeent/container_state_running.hpp"

namespace navagraha {
namespace kubeent {

char CONTAINER_STATE_RUNNING_STARTED_AT[] = "startedAt";

void container_state_running::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->started_at);
}

}
}
