#include "kubeent/selinux_options.hpp"

namespace navagraha {
namespace kubeent {

char SELINUX_OPTIONS_LEVEL[] = "level";
char SELINUX_OPTIONS_ROLE[] = "role";
char SELINUX_OPTIONS_TYPE[] = "type";
char SELINUX_OPTIONS_USER[] = "user";

void selinux_options::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->level)
        .add(this->role)
        .add(this->type)
        .add(this->user);
}

}
}
