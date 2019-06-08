#ifndef _NAVAGRAHA_KUBEENT_CONFIG_MAP_VOLUME_SOURCE_H
#define _NAVAGRAHA_KUBEENT_CONFIG_MAP_VOLUME_SOURCE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/key_to_path.hpp"

namespace navagraha {
namespace kubeent {

extern char KEY_TO_PATH_DEFAULT_MODE[];
extern char KEY_TO_PATH_ITEMS[];
extern char KEY_TO_PATH_NAME[];
extern char KEY_TO_PATH_OPTIONAL[];

class config_map_volume_source : public extensions::serializable<config_map_volume_source> {
public:
    extensions::field<int, KEY_TO_PATH_DEFAULT_MODE> default_mode;
    extensions::field<
        extensions::special_list<key_to_path>,
        KEY_TO_PATH_ITEMS> items;
    extensions::field<std::string, KEY_TO_PATH_NAME> name;
    extensions::field<bool, KEY_TO_PATH_OPTIONAL> optional;

    void bind(extensions::serializer_helper & helper);

};

}
}

#endif
