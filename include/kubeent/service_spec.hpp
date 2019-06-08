#ifndef _NAVAGRAHA_KUBEENT_SERVICE_SPEC_H
#define _NAVAGRAHA_KUBEENT_SERVICE_SPEC_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/common_object.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/service_port.hpp"
#include "kubeent/session_affinity_config.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char SERVICE_SPEC_CLUSTER_IP[];
extern char SERVICE_SPEC_EXTERNAL_IPS[];
extern char SERVICE_SPEC_EXTERNAL_NAME[];
extern char SERVICE_SPEC_EXTERNAL_TRAFFIC_POLICY[];
extern char SERVICE_SPEC_HEALTH_CHECK_NODE_PORT[];
extern char SERVICE_SPEC_LOAD_BALANCER_IP[];
extern char SERVICE_SPEC_LOAD_BALANCER_SOURCE_RANGES[];
extern char SERVICE_SPEC_PORTS[];
extern char SERVICE_SPEC_PUBLISH_NOT_READY_ADDRESSES[];
extern char SERVICE_SPEC_SELECTOR[];
extern char SERVICE_SPEC_SESSION_AFFINITY[];
extern char SERVICE_SPEC_SESSION_AFFINITY_CONFIG[];
extern char SERVICE_SPEC_TYPE[];

class service_spec : public extensions::serializable<service_spec> {
public:
    extensions::field<std::string, SERVICE_SPEC_CLUSTER_IP> cluster_ip;
    extensions::field<
        extensions::special_list<std::string>,
        SERVICE_SPEC_EXTERNAL_IPS> external_ips;
    extensions::field<std::string, SERVICE_SPEC_EXTERNAL_NAME> external_name;
    extensions::field<std::string, SERVICE_SPEC_EXTERNAL_TRAFFIC_POLICY> external_traffic_policy;
    extensions::field<int, SERVICE_SPEC_HEALTH_CHECK_NODE_PORT> health_check_node_port;
    extensions::field<std::string, SERVICE_SPEC_LOAD_BALANCER_IP> load_balancer_ip;
    extensions::field<
        extensions::special_list<std::string>,
        SERVICE_SPEC_LOAD_BALANCER_SOURCE_RANGES> load_balancer_source_ranges;
    extensions::field<
        extensions::special_list<service_port>, SERVICE_SPEC_PORTS> ports;
    extensions::field<bool, SERVICE_SPEC_PUBLISH_NOT_READY_ADDRESSES> publish_not_ready_addresses;
    extensions::field<extensions::common_object, SERVICE_SPEC_SELECTOR> selector;
    extensions::field<std::string, SERVICE_SPEC_SESSION_AFFINITY> session_affinity;
    extensions::field<
        session_affinity_config,
        SERVICE_SPEC_SESSION_AFFINITY_CONFIG> session_affinity_config_;
    extensions::field<std::string, SERVICE_SPEC_TYPE> type;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
