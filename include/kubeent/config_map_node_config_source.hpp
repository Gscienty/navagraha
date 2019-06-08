#ifndef _NAVAGRAHA_KUBEENT_CONFIG_MAP_NODE_CONFIG_SOURCE_H
#define _NAVAGRAHA_KUBEENT_CONFIG_MAP_NODE_CONFIG_SOURCE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char CONFIG_MAP_NODE_CONFIG_SOURCE_KUBELET_CONFIG_KEY[];
extern char CONFIG_MAP_NODE_CONFIG_SOURCE_NAME[];
extern char CONFIG_MAP_NODE_CONFIG_SOURCE_NAMESPACE[];
extern char CONFIG_MAP_NODE_CONFIG_SOURCE_RESOURCE_VERSION[];
extern char CONFIG_MAP_NODE_CONFIG_SOURCE_UID[];

class config_map_node_config_source : public extensions::serializable<config_map_node_config_source> {
public:
    extensions::field<
        std::string,
        CONFIG_MAP_NODE_CONFIG_SOURCE_KUBELET_CONFIG_KEY> kubelet_config_key;
    extensions::field<
        std::string,
        CONFIG_MAP_NODE_CONFIG_SOURCE_NAME> name;
    extensions::field<
        std::string,
        CONFIG_MAP_NODE_CONFIG_SOURCE_NAMESPACE> namespace_;
    extensions::field<
        std::string,
        CONFIG_MAP_NODE_CONFIG_SOURCE_RESOURCE_VERSION> resource_version;
    extensions::field<
        std::string,
        CONFIG_MAP_NODE_CONFIG_SOURCE_UID> uid;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
