#include "kubeent/container_status.hpp"

namespace navagraha {
namespace kubeent {

char CONTAINER_STATUS_CONTAINER_ID[] = "containerID";
char CONTAINER_STATUS_IMAGE[] = "image";
char CONTAINER_STATUS_IMAGE_ID[] = "imageID";
char CONTAINER_STATUS_LAST_STATE[] = "lastState";
char CONTAINER_STATUS_NAME[] = "name";
char CONTAINER_STATUS_READY[] = "ready";
char CONTAINER_STATUS_RESTART_COUNT[] = "restartCount";
char CONTAINER_STATUS_STATE[] = "state";

void container_status::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->container_id)
        .add(this->image)
        .add(this->image_id)
        .add(this->last_state)
        .add(this->name)
        .add(this->ready)
        .add(this->restart_count)
        .add(this->state);
}

}
}
