#include "kubeent/config_map_volume_source.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char KEY_TO_PATH_DEFAULT_MODE[] = "defaultMode";
char KEY_TO_PATH_ITEMS[] = "items";
char KEY_TO_PATH_NAME[] = "name";
char KEY_TO_PATH_OPTIONAL[] = "optional";

void config_map_volume_source::serialize(config_map_volume_source & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.default_mode)
        .add(obj.items)
        .add(obj.name)
        .add(obj.optional)
        .serialize(str);
}

}
}
