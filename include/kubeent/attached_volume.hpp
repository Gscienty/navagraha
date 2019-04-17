#ifndef _NAVAGRAHA_KUBEENT_ATTACHED_VOLUME_H
#define _NAVAGRAHA_KUBEENT_ATTACHED_VOLUME_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char ATTACHED_VOLUME_DEVICE_PATH[];
extern char ATTACHED_VOLUME_NAME[];

class attached_volume : public serializable<attached_volume> {
public:
    extensions::field<std::string, ATTACHED_VOLUME_DEVICE_PATH> device_path;
    extensions::field<std::string, ATTACHED_VOLUME_NAME> name;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
