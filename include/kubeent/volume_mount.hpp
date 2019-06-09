#ifndef _NAVAGRAHA_KUBEENT_VOLUME_MOUNT_H
#define _NAVAGRAHA_KUBEENT_VOLUME_MOUNT_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char VOLUME_MOUNT_MOUNT_PATH[];
extern char VOLUME_MOUNT_MOUNT_PROPAGATION[];
extern char VOLUME_MOUNT_NAME[];
extern char VOLUME_MOUNT_READ_ONLY[];
extern char VOLUME_MOUNT_SUB_PATH[];
extern char VOLUME_MOUNT_SUB_PATH_EXPR[];

class volume_mount : public extensions::serializable<volume_mount> {
public:
    extensions::field<std::string, VOLUME_MOUNT_MOUNT_PATH> mount_path;
    extensions::field<std::string, VOLUME_MOUNT_MOUNT_PROPAGATION> mount_propagation;
    extensions::field<std::string, VOLUME_MOUNT_NAME> name;
    extensions::field<bool, VOLUME_MOUNT_READ_ONLY> read_only;
    extensions::field<std::string, VOLUME_MOUNT_SUB_PATH> sub_path;
    extensions::field<std::string, VOLUME_MOUNT_SUB_PATH_EXPR> sub_path_expr;

    void bind(extensions::serializer_helper & helper);
};
}
}

#endif
