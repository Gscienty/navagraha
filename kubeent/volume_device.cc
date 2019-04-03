#include "kubeent/volume_device.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char VOLUME_DEVICE_DEIVCE_PATH[] = "devicePath";
char VOLUME_DEVICE_NAME[] = "name";

void volume_device::serialize(volume_device & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.device_path)
        .add(obj.name)
        .serialize(str);
}
}
}
