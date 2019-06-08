#ifndef _NAVAGRAHA_KUBEENT_SECURITY_CONTEXT_H
#define _NAVAGRAHA_KUBEENT_SECURITY_CONTEXT_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/capabilities.hpp"
#include "kubeent/selinux_options.hpp"

namespace navagraha {
namespace kubeent {

extern char SECURITY_CONTEXT_ALLOW_PRIVILEGE_ESCALATION[];
extern char SECURITY_CONTEXT_CAPABILITIES[];
extern char SECURITY_CONTEXT_PRIVILEGED[];
extern char SECURITY_CONTEXT_PROC_MOUNT[];
extern char SECURITY_CONTEXT_READ_ONLY_ROOT_FILESYSTEM[];
extern char SECURITY_CONTEXT_RUN_AS_GROUP[];
extern char SECURITY_CONTEXT_RUN_AS_NON_ROOT[];
extern char SECURITY_CONTEXT_RUN_AS_USER[];
extern char SECURITY_CONTEXT_SELINUX_OPTIONS[];

class security_context : public extensions::serializable<security_context> {
public:
    extensions::field<
        bool,
        SECURITY_CONTEXT_ALLOW_PRIVILEGE_ESCALATION> allow_privilege_escalation;
    extensions::field<
        capabilities,
        SECURITY_CONTEXT_CAPABILITIES> capabilities_;
    extensions::field<
        bool,
        SECURITY_CONTEXT_PRIVILEGED> privileged;
    extensions::field<
        std::string,
        SECURITY_CONTEXT_PROC_MOUNT> proc_mount;
    extensions::field<
        bool,
        SECURITY_CONTEXT_READ_ONLY_ROOT_FILESYSTEM> read_only_root_filesystem;
    extensions::field<
        int,
        SECURITY_CONTEXT_RUN_AS_GROUP> run_as_group;
    extensions::field<
        bool,
        SECURITY_CONTEXT_RUN_AS_NON_ROOT> run_as_non_root;
    extensions::field<
        int,
        SECURITY_CONTEXT_RUN_AS_USER> run_as_user;
    extensions::field<
        selinux_options,
        SECURITY_CONTEXT_SELINUX_OPTIONS> selinux_options_;

    void bind(extensions::serializer_helper & helper);
};
}
}

#endif
