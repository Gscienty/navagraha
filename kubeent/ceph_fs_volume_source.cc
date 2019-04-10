#include "kubeent/ceph_fs_volume_source.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char CEPH_FS_VOLUME_SOURCE_MONITORS[] = "monitors";
char CEPH_FS_VOLUME_SOURCE_PATH[] = "path";
char CEPH_FS_VOLUME_SOURCE_READ_ONLY[] = "readOnly";
char CEPH_FS_VOLUME_SOURCE_SECRET_FILE[] = "secretFile";
char CEPH_FS_VOLUME_SOURCE_SECRET_REF[] = "secretRef";
char CEPH_FS_VOLUME_SOURCE_USER[] = "user";

void ceph_fs_volume_source::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->monitors)
        .add(this->path)
        .add(this->read_only)
        .add(this->secret_file)
        .add(this->secret_ref)
        .add(this->user);
}

}
}
