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

void ceph_fs_volume_source::serialize(ceph_fs_volume_source & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.monitors)
        .add(obj.path)
        .add(obj.read_only)
        .add(obj.secret_file)
        .add(obj.secret_ref)
        .add(obj.user)
        .serialize(str);
}

}
}
