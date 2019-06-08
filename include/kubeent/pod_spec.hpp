#ifndef _NAVAGRAHA_KUBEENT_POD_SPEC_H
#define _NAVAGRAHA_KUBEENT_POD_SPEC_H

#include "extensions/field.hpp"
#include "extensions/common_object.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/affinity.hpp"
#include "kubeent/container.hpp"
#include "kubeent/pod_dns_config.hpp"
#include "kubeent/host_alias.hpp"
#include "kubeent/local_object_reference.hpp"
#include "kubeent/pod_readiness_gate.hpp"
#include "kubeent/pod_security_context.hpp"
#include "kubeent/toleration.hpp"
#include "kubeent/volume.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char POD_SPEC_ACTIVE_DEADLINE_SECONDS[];
extern char POD_SPEC_AFFINITY[];
extern char POD_SPEC_AUTOMOUNT_SERVICE_ACCOUNT_TOKEN[];
extern char POD_SPEC_CONTAINERS[];
extern char POD_SPEC_DNS_CONFIG[];
extern char POD_SPEC_DNS_POLICY[];
extern char POD_SPEC_ENABLE_SERVICE_LINKS[];
extern char POD_SPEC_HOST_ALIASES[];
extern char POD_SPEC_HOST_IPC[];
extern char POD_SPEC_HOST_NETWORK[];
extern char POD_SPEC_HOST_PID[];
extern char POD_SPEC_HOSTNAME[];
extern char POD_SPEC_IMAGE_PULL_SECRETS[];
extern char POD_SPEC_INIT_CONTAINERS[];
extern char POD_SPEC_NODE_NAME[];
extern char POD_SPEC_NODE_SELECTOR[];
extern char POD_SPEC_PRIORITY[];
extern char POD_SPEC_PRIORITY_CLASS_NAME[];
extern char POD_SPEC_READINESS_GATES[];
extern char POD_SPEC_RESTART_POLICY[];
extern char POD_SPEC_RUNTIME_CLASS_NAME[];
extern char POD_SPEC_SCHEDULER_NAME[];
extern char POD_SPEC_SECURITY_CONTEXT[];
extern char POD_SPEC_SERVICE_ACCOUNT[];
extern char POD_SPEC_SERVICE_ACCOUNT_NAME[];
extern char POD_SPEC_SHARE_PROCESS_NAMESPACE[];
extern char POD_SPEC_SUBDOMAIN[];
extern char POD_SPEC_TERMINATION_GRACE_PERIOD_SECONDS[];
extern char POD_SPEC_TOLERATIONS[];
extern char POD_SPEC_VOLUMES[];

class pod_spec : public extensions::serializable<pod_spec> {
public:
    extensions::field<int, POD_SPEC_ACTIVE_DEADLINE_SECONDS> active_deadline_seconds;
    extensions::field<affinity, POD_SPEC_AFFINITY> affinity_;
    extensions::field<bool, POD_SPEC_AUTOMOUNT_SERVICE_ACCOUNT_TOKEN> automount_service_account_token;
    extensions::field<
        extensions::special_list<container>, POD_SPEC_CONTAINERS> containers;
    extensions::field<pod_dns_config, POD_SPEC_DNS_CONFIG> dns_config;
    extensions::field<std::string, POD_SPEC_DNS_POLICY> dns_policy;
    extensions::field<bool, POD_SPEC_ENABLE_SERVICE_LINKS> enable_service_links;
    extensions::field<
        extensions::special_list<host_alias>, POD_SPEC_HOST_ALIASES> host_aliases;
    extensions::field<bool, POD_SPEC_HOST_IPC> host_ipc;
    extensions::field<bool, POD_SPEC_HOST_NETWORK> host_network;
    extensions::field<bool, POD_SPEC_HOST_PID> host_pid;
    extensions::field<std::string, POD_SPEC_HOSTNAME> hostname;
    extensions::field<
        extensions::special_list<local_object_reference>,
        CONTAINER_IMAGE_PULL_POLICY> image_pull_policy;
    extensions::field<
        extensions::special_list<container>, POD_SPEC_INIT_CONTAINERS> init_containers;
    extensions::field<std::string, POD_SPEC_NODE_NAME> node_name;
    extensions::field<extensions::common_object, POD_SPEC_NODE_SELECTOR> node_selector;
    extensions::field<int, POD_SPEC_PRIORITY> priority;
    extensions::field<std::string, POD_SPEC_PRIORITY_CLASS_NAME> priority_class_name;
    extensions::field<
        extensions::special_list<pod_readiness_gate>,
        POD_SPEC_READINESS_GATES> readiness_gates;
    extensions::field<std::string, POD_SPEC_RESTART_POLICY> restart_policy;
    extensions::field<std::string, POD_SPEC_RUNTIME_CLASS_NAME> runtime_class_name;
    extensions::field<std::string, POD_SPEC_SCHEDULER_NAME> schedular_name;
    extensions::field<pod_security_context, POD_SPEC_SECURITY_CONTEXT> security_context;
    extensions::field<std::string, POD_SPEC_SERVICE_ACCOUNT> service_account;
    extensions::field<std::string, POD_SPEC_SERVICE_ACCOUNT_NAME> service_account_name;
    extensions::field<bool, POD_SPEC_SHARE_PROCESS_NAMESPACE> share_process_namespace;
    extensions::field<std::string, POD_SPEC_SUBDOMAIN> subdomain;
    extensions::field<int, POD_SPEC_TERMINATION_GRACE_PERIOD_SECONDS> termination_grace_period_seconds;
    extensions::field<
        extensions::special_list<toleration>, POD_SPEC_TOLERATIONS> tolerations;
    extensions::field<
        extensions::special_list<volume>, POD_SPEC_VOLUMES> volumes;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
