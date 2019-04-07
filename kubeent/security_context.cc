#include "kubeent/security_context.hpp"
#include "extensions/link_serializer.hpp"

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

void security_context::serialize(security_context & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.allow_privilege_escalation)
        .add(obj.capabilities_)
        .add(obj.privileged)
        .add(obj.proc_mount)
        .add(obj.read_only_root_filesystem)
        .add(obj.run_as_group)
        .add(obj.run_as_non_root)
        .add(obj.run_as_user)
        .add(obj.selinux_options_)
        .serialize(str);
}
}
}
