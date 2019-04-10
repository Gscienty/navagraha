#include "kubeent/pod_spec.hpp"

namespace navagraha {
namespace kubeent {

char POD_SPEC_ACTIVE_DEADLINE_SECONDS[] = "activeDeadlineSeconds";
char POD_SPEC_AFFINITY[] = "affinity";
char POD_SPEC_AUTOMOUNT_SERVICE_ACCOUNT_TOKEN[] = "automountServiceAccountToken";
char POD_SPEC_CONTAINERS[] = "containers";
char POD_SPEC_DNS_CONFIG[] = "dnsConfig";
char POD_SPEC_DNS_POLICY[] = "dnsPolicy";
char POD_SPEC_ENABLE_SERVICE_LINKS[] = "enableServiceLinks";
char POD_SPEC_HOST_ALIASES[] = "hostAliases";
char POD_SPEC_HOST_IPC[] = "hostIPC";
char POD_SPEC_HOST_NETWORK[] = "hostNetwork";
char POD_SPEC_HOST_PID[] = "hostPID";
char POD_SPEC_HOSTNAME[] = "hostname";
char POD_SPEC_IMAGE_PULL_SECRETS[] = "imagePullSecrets";
char POD_SPEC_INIT_CONTAINERS[] = "initContainers";
char POD_SPEC_NODE_NAME[] = "nodeName";
char POD_SPEC_NODE_SELECTOR[] = "nodeSelector";
char POD_SPEC_PRIORITY[] = "priority";
char POD_SPEC_PRIORITY_CLASS_NAME[] = "priorityClassName";
char POD_SPEC_READINESS_GATES[] = "readinessGates";
char POD_SPEC_RESTART_POLICY[] = "restartPolicy";
char POD_SPEC_RUNTIME_CLASS_NAME[] = "runtimeClassName";
char POD_SPEC_SCHEDULER_NAME[] = "schedulerName";
char POD_SPEC_SECURITY_CONTEXT[] = "securityContext";
char POD_SPEC_SERVICE_ACCOUNT[] = "serviceAccount";
char POD_SPEC_SERVICE_ACCOUNT_NAME[] = "serviceAccountName";
char POD_SPEC_SHARE_PROCESS_NAMESPACE[] = "shareProcessNamespace";
char POD_SPEC_SUBDOMAIN[] = "subdomain";
char POD_SPEC_TERMINATION_GRACE_PERIOD_SECONDS[] = "terminationGracePeriodSeconds";
char POD_SPEC_TOLERATIONS[] = "tolerations";
char POD_SPEC_VOLUMES[] = "volumes";

void pod_spec::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->active_deadline_seconds)
        .add(this->affinity_)
        .add(this->automount_service_account_token)
        .add(this->containers)
        .add(this->dns_config)
        .add(this->dns_policy)
        .add(this->enable_service_links)
        .add(this->hostname)
        .add(this->host_aliases)
        .add(this->host_ipc)
        .add(this->host_network)
        .add(this->host_pid)
        .add(this->image_pull_policy)
        .add(this->init_containers)
        .add(this->node_name)
        .add(this->node_selector)
        .add(this->priority)
        .add(this->priority_class_name)
        .add(this->readiness_gates)
        .add(this->restart_policy)
        .add(this->runtime_class_name)
        .add(this->schedular_name)
        .add(this->security_context)
        .add(this->service_account)
        .add(this->service_account_name)
        .add(this->share_process_namespace)
        .add(this->subdomain)
        .add(this->termination_grace_period_seconds)
        .add(this->tolerations)
        .add(this->volumes);
}

}
}
