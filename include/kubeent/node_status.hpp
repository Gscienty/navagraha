#ifndef _NAVAGRAHA_KUBEENT_NODE_STATUS_H
#define _NAVAGRAHA_KUBEENT_NODE_STATUS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/common_object.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/node_address.hpp"
#include "kubeent/node_condition.hpp"
#include "kubeent/node_config_status.hpp"
#include "kubeent/node_daemon_endpoints.hpp"
#include "kubeent/container_image.hpp"
#include "kubeent/node_system_info.hpp"
#include "kubeent/attached_volume.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char NODE_STATUS_ADDRESSES[];
extern char NODE_STATUS_ALLOCATABLE[];
extern char NODE_STATUS_CAPACITY[];
extern char NODE_STATUS_CONDITIONS[];
extern char NODE_STATUS_CONFIG[];
extern char NODE_STATUS_DAEMON_ENDPOINTS[];
extern char NODE_STATUS_IMAGES[];
extern char NODE_STATUS_NODE_INFO[];
extern char NODE_STATUS_PHASE[];
extern char NODE_STATUS_VOLUMES_ATTACHED[];
extern char NODE_STATUS_VOLUMES_IN_USE[];

class node_status : public serializable<node_status> {
public:
    extensions::field<
        extensions::special_list<node_address>, NODE_STATUS_ADDRESSES> addresses;
    extensions::field<
        extensions::common_object, NODE_STATUS_ALLOCATABLE> allocatable;
    extensions::field<
        extensions::common_object, NODE_STATUS_CAPACITY> capacity;
    extensions::field<
        extensions::special_list<node_condition>, NODE_STATUS_CONDITIONS> conditions;
    extensions::field<node_config_status, NODE_STATUS_CONFIG> config;
    extensions::field<node_daemon_endpoints, NODE_STATUS_DAEMON_ENDPOINTS> daemon_endpoints;
    extensions::field<
        extensions::special_list<container_image>, NODE_STATUS_IMAGES> images;
    extensions::field<node_system_info, NODE_STATUS_NODE_INFO> node_info;
    extensions::field<std::string, NODE_STATUS_PHASE> phase;
    extensions::field<
        extensions::special_list<attached_volume>, NODE_STATUS_VOLUMES_ATTACHED> volumes_attached;
    extensions::field<
        extensions::special_list<std::string>, NODE_STATUS_VOLUMES_IN_USE> volumes_in_use;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
