#include "kubeent/attached_volume.hpp"

namespace navagraha {
namespace kubeent {

char ATTACHED_VOLUME_DEVICE_PATH[] = "devicePath";
char ATTACHED_VOLUME_NAME[] = "name";

void attached_volume::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->device_path)
        .add(this->name);
}

}
}
