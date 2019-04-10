#include "kubeent/cinder_volume_source.hpp"

namespace navagraha {
namespace kubeent {

char CINDER_VOLUME_SOURCE_FS_TYPE[] = "fsType";
char CINDER_VOLUME_SOURCE_READ_ONLY[] = "readOnly";
char CINDER_VOLUME_SOURCE_SECRET_REF[] = "secretRef";
char CINDER_VOLUME_SOURCE_VOLUME_ID[] = "volumeID";

void cinder_volume_source::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->fs_type)
        .add(this->read_only)
        .add(this->secret_ref)
        .add(this->volume_id);
}
}
}
