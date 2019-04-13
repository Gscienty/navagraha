#include "kubeent/service_spec.hpp"

namespace navagraha {
namespace kubeent {

char SERVICE_SPEC_CLUSTER_IP[] = "clusterIP";
char SERVICE_SPEC_EXTERNAL_IPS[] = "externalIPs";
char SERVICE_SPEC_EXTERNAL_NAME[] = "externalName";
char SERVICE_SPEC_EXTERNAL_TRAFFIC_POLICY[] = "externalTrafficPolicy";
char SERVICE_SPEC_HEALTH_CHECK_NODE_PORT[] = "healthCheckNodePort";
char SERVICE_SPEC_LOAD_BALANCER_IP[] = "loadBalancerIP";
char SERVICE_SPEC_LOAD_BALANCER_SOURCE_RANGES[] = "loadBalancerSourceRanges";
char SERVICE_SPEC_PORTS[] = "ports";
char SERVICE_SPEC_PUBLISH_NOT_READY_ADDRESSES[] = "publishNotReadyAddresses";
char SERVICE_SPEC_SELECTOR[] = "selector";
char SERVICE_SPEC_SESSION_AFFINITY[] = "sessionAffinity";
char SERVICE_SPEC_SESSION_AFFINITY_CONFIG[] = "sessionAffinityConfig";
char SERVICE_SPEC_TYPE[] = "type";

void service_spec::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->cluster_ip)
        .add(this->external_ips)
        .add(this->external_name)
        .add(this->external_traffic_policy)
        .add(this->health_check_node_port)
        .add(this->load_balancer_ip)
        .add(this->load_balancer_source_ranges)
        .add(this->ports)
        .add(this->publish_not_ready_addresses)
        .add(this->selector)
        .add(this->session_affinity)
        .add(this->session_affinity_config_)
        .add(this->type);
}

}
}
