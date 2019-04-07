#include "kubeent/pod_spec.hpp"
#include "extensions/link_serializer.hpp"

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

void pod_spec::serialize(pod_spec & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.active_deadline_seconds)
        .add(obj.affinity_)
        .add(obj.automount_service_account_token)
        .add(obj.containers)
        .add(obj.dns_config)
        .add(obj.dns_policy)
        .add(obj.enable_service_links)
        .add(obj.hostname)
        .add(obj.host_aliases)
        .add(obj.host_ipc)
        .add(obj.host_network)
        .add(obj.host_pid)
        .add(obj.image_pull_policy)
        .add(obj.init_containers)
        .add(obj.node_name)
        .add(obj.node_selector)
        .add(obj.priority)
        .add(obj.priority_class_name)
        .add(obj.readiness_gates)
        .add(obj.restart_policy)
        .add(obj.runtime_class_name)
        .add(obj.schedular_name)
        .add(obj.security_context)
        .add(obj.service_account)
        .add(obj.service_account_name)
        .add(obj.share_process_namespace)
        .add(obj.subdomain)
        .add(obj.termination_grace_period_seconds)
        .add(obj.tolerations)
        .add(obj.volumes)
        .serialize(str);
}
}
}
