#include "kubeent/config_map_node_config_source.hpp"

namespace navagraha {
namespace kubeent {

char CONFIG_MAP_NODE_CONFIG_SOURCE_KUBELET_CONFIG_KEY[] = "kubeletConfigKey";
char CONFIG_MAP_NODE_CONFIG_SOURCE_NAME[] = "name";
char CONFIG_MAP_NODE_CONFIG_SOURCE_NAMESPACE[] = "namespace";
char CONFIG_MAP_NODE_CONFIG_SOURCE_RESOURCE_VERSION[] = "resourceVersion";
char CONFIG_MAP_NODE_CONFIG_SOURCE_UID[] = "uid";

void config_map_node_config_source::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->kubelet_config_key)
        .add(this->name)
        .add(this->namespace_)
        .add(this->resource_version)
        .add(this->uid);
}

}
}
