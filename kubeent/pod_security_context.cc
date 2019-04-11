#include "kubeent/pod_security_context.hpp"

namespace navagraha {
namespace kubeent {

char POD_SECURITY_CONTEXT_FS_GROUP[] = "fsGroup";
char POD_SECURITY_CONTEXT_RUN_AS_GROUP[] = "runAsGroup";
char POD_SECURITY_CONTEXT_RUN_AS_NON_ROOT[] = "runAsNonRoot";
char POD_SECURITY_CONTEXT_RUN_AS_USER[] = "runAsUser";
char POD_SECURITY_CONTEXT_SELINUX_OPTIONS[] = "seLinuxOptions";
char POD_SECURITY_CONTEXT_SUPPLEMENTAL_GROUPS[] = "supplementalGroups";
char POD_SECURITY_CONTEXT_SYSCTLS[] = "sysctls";

void pod_security_context::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->fs_group)
        .add(this->run_as_group)
        .add(this->run_as_non_root)
        .add(this->run_as_user)
        .add(this->selinux_options_)
        .add(this->supplemental_groups)
        .add(this->sysctls);
}

}
}
