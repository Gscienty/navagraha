#include "kubeent/security_context.hpp"

namespace navagraha {
namespace kubeent {

char SECURITY_CONTEXT_ALLOW_PRIVILEGE_ESCALATION[] = "allowPrivilegeEscalation";
char SECURITY_CONTEXT_CAPABILITIES[] = "capabilities";
char SECURITY_CONTEXT_PRIVILEGED[] = "privileged";
char SECURITY_CONTEXT_PROC_MOUNT[] = "procMount";
char SECURITY_CONTEXT_READ_ONLY_ROOT_FILESYSTEM[] = "readOnlyRootFilesystem";
char SECURITY_CONTEXT_RUN_AS_GROUP[] = "runAsGroup";
char SECURITY_CONTEXT_RUN_AS_NON_ROOT[] = "runAsNonRoot";
char SECURITY_CONTEXT_RUN_AS_USER[] = "runAsUser";
char SECURITY_CONTEXT_SELINUX_OPTIONS[] = "seLinuxOptions";

void security_context::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->allow_privilege_escalation)
        .add(this->capabilities_)
        .add(this->privileged)
        .add(this->proc_mount)
        .add(this->read_only_root_filesystem)
        .add(this->run_as_group)
        .add(this->run_as_non_root)
        .add(this->run_as_user)
        .add(this->selinux_options_);
}

}
}
