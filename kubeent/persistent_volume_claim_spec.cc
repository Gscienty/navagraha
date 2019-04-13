#include "kubeent/persistent_volume_claim_spec.hpp"

namespace navagraha {
namespace kubeent {

char PERSISTENT_VOLUME_CLAIM_SPEC_ACCESS_MODES[] = "accessModes";
char PERSISTENT_VOLUME_CLAIM_SPEC_DATA_SOURCE[] = "dataSource";
char PERSISTENT_VOLUME_CLAIM_SPEC_RESOURCES[] = "resources";
char PERSISTENT_VOLUME_CLAIM_SPEC_SELECTOR[] = "selector";
char PERSISTENT_VOLUME_CLAIM_SPEC_STORAGE_CLASS_NAME[] = "storageClassName";
char PERSISTENT_VOLUME_CLAIM_SPEC_VOLUME_MODE[] = "volumeMode";
char PERSISTENT_VOLUME_CLAIM_SPEC_VOLUME_NAME[] = "volumeName";

void persistent_volume_claim_spec::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->access_modes)
        .add(this->data_source)
        .add(this->resources)
        .add(this->selector)
        .add(this->storage_class_name)
        .add(this->volume_mode)
        .add(this->volume_name);
}

}
}
