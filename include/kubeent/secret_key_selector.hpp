#ifndef _NAVAGRAHA_KUBEENT_SECRET_KEY_SELECTOR_H
#define _NAVAGRAHA_KUBEENT_SECRET_KEY_SELECTOR_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char SECRET_KEY_SELECTOR_KEY[];
extern char SECRET_KEY_SELECTOR_NAME[];
extern char SECRET_KEY_SELECTOR_OPTIONAL[];

class secret_key_selector : public serializable<secret_key_selector> {
public:
    extensions::field<
        std::string,
        SECRET_KEY_SELECTOR_KEY> key;
    extensions::field<
        std::string,
        SECRET_KEY_SELECTOR_NAME> name;
    extensions::field<
        bool,
        SECRET_KEY_SELECTOR_OPTIONAL> optional;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
