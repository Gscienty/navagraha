#ifndef _NAVAGRAHA_KUBEENT_POD_SECURITY_CONTEXT_H
#define _NAVAGRAHA_KUBEENT_POD_SECURITY_CONTEXT_H

#include "extensions/field.hpp"
#include "extensions/list_wrapper.hpp"
#include "kubeent/selinux_options.hpp"
#include "kubeent/sysctl.hpp"

namespace navagraha {
namespace kubeent {

extern char POD_SECURITY_CONTEXT_FS_GROUP[];
extern char POD_SECURITY_CONTEXT_RUN_AS_GROUP[];
extern char POD_SECURITY_CONTEXT_RUN_AS_NON_ROOT[];
extern char POD_SECURITY_CONTEXT_RUN_AS_USER[];
extern char POD_SECURITY_CONTEXT_SELINUX_OPTIONS[];
extern char POD_SECURITY_CONTEXT_SUPPLEMENTAL_GROUPS[];
extern char POD_SECURITY_CONTEXT_SYSCTLS[];

class pod_security_context {
public:
    extensions::field<int, POD_SECURITY_CONTEXT_FS_GROUP> fs_group;
    extensions::field<int, POD_SECURITY_CONTEXT_RUN_AS_GROUP> run_as_group;
    extensions::field<bool, POD_SECURITY_CONTEXT_RUN_AS_NON_ROOT> run_as_non_root;
    extensions::field<int, POD_SECURITY_CONTEXT_RUN_AS_USER> run_as_user;
    extensions::field<selinux_options, POD_SECURITY_CONTEXT_SELINUX_OPTIONS> selinux_options;
    extensions::field<
        extensions::special_list<int>,
        POD_SECURITY_CONTEXT_SUPPLEMENTAL_GROUPS> supplemental_groups;
    extensions::field<
        extensions::special_list<sysctl>,
        POD_SECURITY_CONTEXT_SYSCTLS> sysctls;

    static void serialize(pod_security_context & obj, std::ostringstream & str);
};

}
}

#endif
