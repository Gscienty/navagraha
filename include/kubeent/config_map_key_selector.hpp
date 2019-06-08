#ifndef _NAVAGRAHA_KUBEENT_CONFIG_MAP_KEY_SELECTOR_H
#define _NAVAGRAHA_KUBEENT_CONFIG_MAP_KEY_SELECTOR_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char CONFIG_MAP_KEY_SELECTOR_KEY[];
extern char CONFIG_MAP_KEY_SELECTOR_NAME[];
extern char CONFIG_MAP_KEY_SELECTOR_OPTIONAL[];

class config_map_key_selector : public extensions::serializable<config_map_key_selector> {
public:
    extensions::field<
        std::string,
        CONFIG_MAP_KEY_SELECTOR_KEY> key;
    extensions::field<
        std::string,
        CONFIG_MAP_KEY_SELECTOR_NAME> name;
    extensions::field<
        bool,
        CONFIG_MAP_KEY_SELECTOR_OPTIONAL> optional;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
