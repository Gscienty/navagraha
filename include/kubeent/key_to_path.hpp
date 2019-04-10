#ifndef _NAVAGRAHA_KUBEENT_KEY_TO_PATH_H
#define _NAVAGRAHA_KUBEENT_KEY_TO_PATH_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"

namespace navagraha {
namespace kubeent {

extern char KEY_TO_PATH_KEY[];
extern char KEY_TO_PATH_MODE[];
extern char KEY_TO_PATH_PATH[];

class key_to_path : public serializable<key_to_path> {
public:
    extensions::field<std::string, KEY_TO_PATH_KEY> key;
    extensions::field<int, KEY_TO_PATH_MODE> mode;
    extensions::field<std::string, KEY_TO_PATH_PATH> path;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
