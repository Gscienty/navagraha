#ifndef _NAVAGRAHA_KUBEENT_VOLUME_MOUNT_H
#define _NAVAGRAHA_KUBEENT_VOLUME_MOUNT_H

#include "extensions/field.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char VOLUME_MOUNT_MOUNT_PATH[];
extern char VOLUME_MOUNT_MOUNT_PROPAGATION[];
extern char VOLUME_MOUNT_NAME[];
extern char VOLUME_MOUNT_READ_ONLY[];
extern char VOLUME_MOUNT_SUB_PATH[];

class volume_mount {
public:
    extensions::field<std::string, VOLUME_MOUNT_MOUNT_PATH> mount_path;
    extensions::field<std::string, VOLUME_MOUNT_MOUNT_PROPAGATION> mount_propagation;
    extensions::field<bool, VOLUME_MOUNT_READ_ONLY> read_only;
    extensions::field<std::string, VOLUME_MOUNT_SUB_PATH> sub_path;

    static void serialize(volume_mount & obj, std::ostringstream & str);
};
}
}

#endif
