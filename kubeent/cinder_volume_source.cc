#include "kubeent/cinder_volume_source.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char CINDER_VOLUME_SOURCE_FS_TYPE[] = "fsType";
char CINDER_VOLUME_SOURCE_READ_ONLY[] = "readOnly";
char CINDER_VOLUME_SOURCE_SECRET_REF[] = "secretRef";
char CINDER_VOLUME_SOURCE_VOLUME_ID[] = "volumeID";

void cinder_volume_source::serialize(cinder_volume_source & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.fs_type)
        .add(obj.read_only)
        .add(obj.secret_ref)
        .add(obj.volume_id)
        .serialize(str);
}

}
}
