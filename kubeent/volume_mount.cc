#include "kubeent/volume_mount.hpp"

namespace navagraha {
namespace kubeent {

char VOLUME_MOUNT_MOUNT_PATH[] = "mountPath";
char VOLUME_MOUNT_MOUNT_PROPAGATION[] = "mountPropagation";
char VOLUME_MOUNT_NAME[] = "name";
char VOLUME_MOUNT_READ_ONLY[] = "readOnly";
char VOLUME_MOUNT_SUB_PATH[] = "subPath";

void volume_mount::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->mount_path)
        .add(this->mount_propagation)
        .add(this->read_only)
        .add(this->sub_path);
}

}
}
