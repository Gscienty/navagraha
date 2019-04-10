#include "kubeent/volume_device.hpp"

namespace navagraha {
namespace kubeent {

char VOLUME_DEVICE_DEIVCE_PATH[] = "devicePath";
char VOLUME_DEVICE_NAME[] = "name";

void volume_device::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->device_path)
        .add(this->name);
}

}
}
