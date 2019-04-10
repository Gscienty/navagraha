#include "kubeent/quobyte_volume_source.hpp"

namespace navagraha {
namespace kubeent {

char QUOBYTE_VOLUME_SOURCE_GROUP[] = "group";
char QUOBYTE_VOLUME_SOURCE_READ_ONLY[] = "readOnly";
char QUOBYTE_VOLUME_SOURCE_REGISTRY[] = "registry";
char QUOBYTE_VOLUME_SOURCE_USER[] = "user";
char QUOBYTE_VOLUME_SOURCE_VOLUME[] = "volume";

void quobyte_volume_source::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->group)
        .add(this->read_only)
        .add(this->registry)
        .add(this->user)
        .add(this->volume);
}

}
}
