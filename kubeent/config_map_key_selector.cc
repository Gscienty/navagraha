#include "kubeent/config_map_key_selector.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char CONFIG_MAP_KEY_SELECTOR_KEY[] = "key";
char CONFIG_MAP_KEY_SELECTOR_NAME[] = "name";
char CONFIG_MAP_KEY_SELECTOR_OPTIONAL[] = "optional";

void config_map_key_selector::serialize(config_map_key_selector & obj, std::ostringstream & str)\
{
    extensions::link_serializer()
        .add(obj.key)
        .add(obj.name)
        .add(obj.optional)
        .serialize(str);
}

}
}
