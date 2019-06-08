#ifndef _NAVAGRAHA_KUBEENT_NODE_CONFIG_SOURCE_H
#define _NAVAGRAHA_KUBEENT_NODE_CONFIG_SOURCE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/config_map_node_config_source.hpp"

namespace navagraha {
namespace kubeent {

extern char NODE_CONFIG_SOURCE_CONFIG_MAP[];

class node_config_source : public extensions::serializable<node_config_source> {
public:
    extensions::field<
        config_map_node_config_source,
        NODE_CONFIG_SOURCE_CONFIG_MAP> config_map;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
