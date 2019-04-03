#include "kubeent/volume.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char VOLUME_CEPHFS[] = "cephfs";
char VOLUME_CINDER[] = "cinder";
char VOLUME_CONFIG_MAP[] = "configMap";
char VOLUME_DOWNWARD_API[] = "downwardAPI";
char VOLUME_EMPTY_DIR[] = "emptyDir";
char VOLUME_NAME[] = "name";

void volume::serialize(volume & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.cephfs)
        .add(obj.cinder)
        .add(obj.config_map)
        .add(obj.downward_api)
        .add(obj.empty_dir)
        .add(obj.name)
        .serialize(str);
}

}
}
