#ifndef _NAVAGRAHA_KUBEENT_CEPH_FS_VOLUME_SOURCE_H
#define _NAVAGRAHA_KUBEENT_CEPH_FS_VOLUME_SOURCE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "kubeent/local_object_reference.hpp"
#include "extensions/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char CEPH_FS_VOLUME_SOURCE_MONITORS[];
extern char CEPH_FS_VOLUME_SOURCE_PATH[];
extern char CEPH_FS_VOLUME_SOURCE_READ_ONLY[];
extern char CEPH_FS_VOLUME_SOURCE_SECRET_FILE[];
extern char CEPH_FS_VOLUME_SOURCE_SECRET_REF[];
extern char CEPH_FS_VOLUME_SOURCE_USER[];

class ceph_fs_volume_source : public extensions::serializable<ceph_fs_volume_source> {
public:
    extensions::field<
        extensions::special_list<std::string>,
        CEPH_FS_VOLUME_SOURCE_MONITORS> monitors;
    extensions::field<std::string, CEPH_FS_VOLUME_SOURCE_PATH> path;
    extensions::field<bool, CEPH_FS_VOLUME_SOURCE_READ_ONLY> read_only;
    extensions::field<std::string, CEPH_FS_VOLUME_SOURCE_SECRET_FILE> secret_file;
    extensions::field<
        local_object_reference,
        CEPH_FS_VOLUME_SOURCE_SECRET_REF> secret_ref;
    extensions::field<std::string, CEPH_FS_VOLUME_SOURCE_USER> user;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
