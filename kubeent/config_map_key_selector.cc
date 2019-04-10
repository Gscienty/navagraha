#include "kubeent/config_map_key_selector.hpp"

namespace navagraha {
namespace kubeent {

char CONFIG_MAP_KEY_SELECTOR_KEY[] = "key";
char CONFIG_MAP_KEY_SELECTOR_NAME[] = "name";
char CONFIG_MAP_KEY_SELECTOR_OPTIONAL[] = "optional";

void config_map_key_selector::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->key)
        .add(this->name)
        .add(this->optional);
}
}
}
