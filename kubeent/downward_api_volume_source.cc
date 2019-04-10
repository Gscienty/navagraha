#include "kubeent/downward_api_volume_source.hpp"

namespace navagraha {
namespace kubeent {

char DOWNWARD_API_VOLUME_SOURCE_DEFAULT_MODE[] = "defaultMode";
char DOWNWARD_API_VOLUME_SOURCE_ITEMS[] = "items";

void downward_api_volume_source::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->default_mode)
        .add(this->items);
}

}
}
