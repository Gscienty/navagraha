#include "kubeent/config_map_volume_source.hpp"

namespace navagraha {
namespace kubeent {

char KEY_TO_PATH_DEFAULT_MODE[] = "defaultMode";
char KEY_TO_PATH_ITEMS[] = "items";
char KEY_TO_PATH_NAME[] = "name";
char KEY_TO_PATH_OPTIONAL[] = "optional";

void config_map_volume_source::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->default_mode)
        .add(this->items)
        .add(this->name)
        .add(this->optional);
}
}
}
