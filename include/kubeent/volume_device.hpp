#ifndef _NAVAGRAHA_KUBEENT_VOLUME_DEVICE_H
#define _NAVAGRAHA_KUBEENT_VOLUME_DEVICE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char VOLUME_DEVICE_DEIVCE_PATH[];
extern char VOLUME_DEVICE_NAME[];

class volume_device : public extensions::serializable<volume_device> {
public:
    extensions::field<std::string, VOLUME_DEVICE_DEIVCE_PATH> device_path;
    extensions::field<std::string, VOLUME_DEVICE_NAME> name;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
