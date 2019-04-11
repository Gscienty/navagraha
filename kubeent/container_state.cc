#include "kubeent/container_state.hpp"

namespace navagraha {
namespace kubeent {

char CONTAINER_STATE_RUNNING[] = "running";
char CONTAINER_STATE_TERMINATED[] = "terminated";
char CONTAINER_STATE_WAITING[] = "waiting";

void container_state::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->running)
        .add(this->terminated)
        .add(this->waiting);
}

}
}
