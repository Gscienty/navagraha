#include "kubeent/volume_mount.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char VOLUME_MOUNT_MOUNT_PATH[] = "mountPath";
char VOLUME_MOUNT_MOUNT_PROPAGATION[] = "mountPropagation";
char VOLUME_MOUNT_NAME[] = "name";
char VOLUME_MOUNT_READ_ONLY[] = "readOnly";
char VOLUME_MOUNT_SUB_PATH[] = "subPath";

void volume_mount::serialize(volume_mount & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.mount_path)
        .add(obj.mount_propagation)
        .add(obj.read_only)
        .add(obj.sub_path)
        .serialize(str);
}

}
}
