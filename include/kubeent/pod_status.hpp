#ifndef _NAVAGRAHA_KUBEENT_POD_STATUS_H
#define _NAVAGRAHA_KUBEENT_POD_STATUS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/time.hpp"
#include "kubeent/pod_condition.hpp"
#include "kubeent/container_status.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char POD_STATUS_CONDITIONS[];
extern char POD_STATUS_CONTAINER_STATUSES[];
extern char POD_STATUS_HOST_IP[];
extern char POD_STATUS_INIT_CONTAINER_STATUSES[];
extern char POD_STATUS_MESSAGE[];
extern char POD_STATUS_NOMINATED_NODE_NAME[];
extern char POD_STATUS_PHASE[];
extern char POD_STATUS_POD_IP[];
extern char POD_STATUS_QOS_CLASS[];
extern char POD_STATUS_REASON[];
extern char POD_STATUS_START_TIME[];

class pod_status : public extensions::serializable<pod_status> {
public:
    extensions::field<
        extensions::special_list<pod_condition>,
        POD_STATUS_CONDITIONS> conditions;
    extensions::field<
        extensions::special_list<container_status>,
        POD_STATUS_CONTAINER_STATUSES> container_statuses;
    extensions::field<std::string, POD_STATUS_HOST_IP> host_ip;
    extensions::field<
        extensions::special_list<container_status>,
        POD_STATUS_INIT_CONTAINER_STATUSES> init_container_statuses;
    extensions::field<std::string, POD_STATUS_MESSAGE> message;
    extensions::field<std::string, POD_STATUS_NOMINATED_NODE_NAME> nominated_node_name;
    extensions::field<std::string, POD_STATUS_PHASE> phase;
    extensions::field<std::string, POD_STATUS_POD_IP> pod_ip;
    extensions::field<std::string, POD_STATUS_QOS_CLASS> qos_class;
    extensions::field<std::string, POD_STATUS_REASON> reason;
    extensions::field<time, POD_STATUS_START_TIME> start_time;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
