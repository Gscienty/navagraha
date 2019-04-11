#include "kubeent/container_state_terminated.hpp"

namespace navagraha {
namespace kubeent {

char CONTAINER_STATE_TERMINATED_CONTAINER_ID[] = "containerID";
char CONTAINER_STATE_TERMINATED_EXIT_CODE[] = "exitCode";
char CONTAINER_STATE_TERMINATED_FINISHED_AT[] = "finishedAt";
char CONTAINER_STATE_TERMINATED_MESSAGE[] = "message";
char CONTAINER_STATE_TERMINATED_REASON[] = "reason";
char CONTAINER_STATE_TERMINATED_SIGNAL[] = "signal";
char CONTAINER_STATE_TERMINATED_STARTED_AT[] = "startedAt";

void container_state_terminated::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->container_id)
        .add(this->exit_code)
        .add(this->finished_at)
        .add(this->message)
        .add(this->reason)
        .add(this->signal)
        .add(this->started_at);
}

}
}
