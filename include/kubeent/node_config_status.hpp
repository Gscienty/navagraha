#ifndef _NAVAGRAHA_KUBEENT_NODE_CONFIG_STATUS_H
#define _NAVAGRAHA_KUBEENT_NODE_CONFIG_STATUS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/node_config_source.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char NODE_CONFIG_STATUS_ACTIVE[];
extern char NODE_CONFIG_STATUS_ASSIGNED[];
extern char NODE_CONFIG_STATUS_ERROR[];
extern char NODE_CONFIG_STATUS_LAST_KNOWN_GOOD[];

class node_config_status : public extensions::serializable<node_config_status> {
public:
    extensions::field<node_config_source, NODE_CONFIG_STATUS_ACTIVE> active;
    extensions::field<node_config_source, NODE_CONFIG_STATUS_ASSIGNED> assigned;
    extensions::field<std::string, NODE_CONFIG_STATUS_ERROR> error;
    extensions::field<node_config_source, NODE_CONFIG_STATUS_LAST_KNOWN_GOOD> last_known_good;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
