#ifndef _NAVAGRAHA_KUBEENT_VOLUME_DEVICE_H
#define _NAVAGRAHA_KUBEENT_VOLUME_DEVICE_H

#include "extensions/field.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char VOLUME_DEVICE_DEIVCE_PATH[];
extern char VOLUME_DEVICE_NAME[];

class volume_device {
public:
    extensions::field<std::string, VOLUME_DEVICE_DEIVCE_PATH> device_path;
    extensions::field<std::string, VOLUME_DEVICE_NAME> name;

    static void serialize(volume_device & obj, std::ostringstream & str);
};

}
}

#endif
