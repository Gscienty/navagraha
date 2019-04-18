#include "kubeent/config_map.hpp"

namespace navagraha {
namespace kubeent {

char CONFIG_MAP_API_VERSION[] = "apiVersion";
char CONFIG_MAP_BINARY_DATA[] = "binaryData";
char CONFIG_MAP_DATA[] = "data";
char CONFIG_MAP_KIND[] = "kind";
char CONFIG_MAP_METADATA[] = "metadata";

void config_map::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->binary_data)
        .add(this->data)
        .add(this->kind)
        .add(this->metadata);
}

}
}
