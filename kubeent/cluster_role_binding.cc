#include "kubeent/cluster_role_binding.hpp"

namespace navagraha {
namespace kubeent {

char CLUSTER_ROLE_BINDING_API_VERSION[] = "apiVersion";
char CLUSTER_ROLE_BINDING_KIND[] = "kind";
char CLUSTER_ROLE_BINDING_METADATA[] = "metadata";
char CLUSTER_ROLE_BINDING_ROLE_REF[] = "roleRef";
char CLUSTER_ROLE_BINDING_SUBJECTS[] = "subjects";

void cluster_role_binding::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->kind)
        .add(this->metadata)
        .add(this->role_ref_)
        .add(this->subjects);
}

}
}
