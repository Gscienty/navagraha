#ifndef _NAVAGRAHA_KUBEENT_CLUSTER_ROLE_BINDING_H
#define _NAVAGRAHA_KUBEENT_CLUSTER_ROLE_BINDING_H

#include "extensions/field.hpp"
#include "extensions/serializable.hpp"
#include "extensions/special_list.hpp"
#include "kubeent/role_ref.hpp"
#include "kubeent/subject.hpp"
#include "kubeent/object_meta.hpp"

namespace navagraha {
namespace kubeent {

extern char CLUSTER_ROLE_BINDING_API_VERSION[];
extern char CLUSTER_ROLE_BINDING_KIND[];
extern char CLUSTER_ROLE_BINDING_METADATA[];
extern char CLUSTER_ROLE_BINDING_ROLE_REF[];
extern char CLUSTER_ROLE_BINDING_SUBJECTS[];

class cluster_role_binding : public extensions::serializable<cluster_role_binding> {
public:
    extensions::field<std::string, CLUSTER_ROLE_BINDING_API_VERSION> api_version;
    extensions::field<std::string, CLUSTER_ROLE_BINDING_KIND> kind;
    extensions::field<object_meta, CLUSTER_ROLE_BINDING_METADATA> metadata;
    extensions::field<role_ref, CLUSTER_ROLE_BINDING_ROLE_REF> role_ref_;
    extensions::field<extensions::special_list<subject>, CLUSTER_ROLE_BINDING_SUBJECTS> subjects;

    void bind(extensions::serializer_helper & helper);
};

}
}
#endif
