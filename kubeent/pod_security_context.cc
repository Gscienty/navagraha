#include "kubeent/pod_security_context.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char POD_SECURITY_CONTEXT_FS_GROUP[] = "fsGroup";
char POD_SECURITY_CONTEXT_RUN_AS_GROUP[] = "runAsGroup";
char POD_SECURITY_CONTEXT_RUN_AS_NON_ROOT[] = "runAsNonRoot";
char POD_SECURITY_CONTEXT_RUN_AS_USER[] = "runAsUser";
char POD_SECURITY_CONTEXT_SELINUX_OPTIONS[] = "seLinuxOptions";
char POD_SECURITY_CONTEXT_SUPPLEMENTAL_GROUPS[] = "supplementalGroups";
char POD_SECURITY_CONTEXT_SYSCTLS[] = "sysctls";

void pod_security_context::serialize(pod_security_context & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.fs_group)
        .add(obj.run_as_group)
        .add(obj.run_as_non_root)
        .add(obj.run_as_user)
        .add(obj.selinux_options)
        .add(obj.supplemental_groups)
        .add(obj.sysctls)
        .serialize(str);
}
}
}
