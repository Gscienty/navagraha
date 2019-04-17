#include "kubeent/node_config_source.hpp"

namespace navagraha {
namespace kubeent {

char NODE_CONFIG_SOURCE_CONFIG_MAP[] = "configMap";

void node_config_source::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->config_map);
}

}
}
