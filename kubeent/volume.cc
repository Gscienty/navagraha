#include "kubeent/volume.hpp"

namespace navagraha {
namespace kubeent {

char VOLUME_CEPHFS[] = "cephfs";
char VOLUME_CINDER[] = "cinder";
char VOLUME_CONFIG_MAP[] = "configMap";
char VOLUME_DOWNWARD_API[] = "downwardAPI";
char VOLUME_EMPTY_DIR[] = "emptyDir";
char VOLUME_NAME[] = "name";

void volume::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->cephfs)
        .add(this->cinder)
        .add(this->config_map)
        .add(this->downward_api)
        .add(this->empty_dir)
        .add(this->name);
}

}
}
