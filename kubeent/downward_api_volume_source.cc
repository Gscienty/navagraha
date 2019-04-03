#include "kubeent/downward_api_volume_source.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char DOWNWARD_API_VOLUME_SOURCE_DEFAULT_MODE[] = "defaultMode";
char DOWNWARD_API_VOLUME_SOURCE_ITEMS[] = "items";

void downward_api_volume_source::serialize(downward_api_volume_source & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.default_mode)
        .add(obj.items)
        .serialize(str);
}

}
}
