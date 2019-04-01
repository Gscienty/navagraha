#include "kubeent/quobyte_volume_source.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char QUOBYTE_VOLUME_SOURCE_GROUP[] = "group";
char QUOBYTE_VOLUME_SOURCE_READ_ONLY[] = "readOnly";
char QUOBYTE_VOLUME_SOURCE_REGISTRY[] = "registry";
char QUOBYTE_VOLUME_SOURCE_USER[] = "user";
char QUOBYTE_VOLUME_SOURCE_VOLUME[] = "volume";

void quobyte_volume_source::serialize(quobyte_volume_source & obj,
                                      std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.group)
        .add(obj.read_only)
        .add(obj.registry)
        .add(obj.volume)
        .serialize(str);
}
}
}
