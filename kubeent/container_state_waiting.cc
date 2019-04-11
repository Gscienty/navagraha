#include "kubeent/container_state_waiting.hpp"

namespace navagraha {
namespace kubeent {

char CONTAINER_STATE_WAITING_MESSAGE[] = "message";
char CONTAINER_STATE_WAITING_REASON[] = "reason";

void container_state_waiting::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->message)
        .add(this->reason);
}

}
}
