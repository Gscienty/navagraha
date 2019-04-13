#ifndef _NAVAGRAHA_KUBEENT_REPLICA_SET_H
#define _NAVAGRAHA_KUBEENT_REPLICA_SET_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/object_meta.hpp"
#include "kubeent/replica_set_spec.hpp"
#include "kubeent/replica_set_status.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char REPLICA_SET_API_VERSION[];
extern char REPLICA_SET_KIND[];
extern char REPLICA_SET_METADATA[];
extern char REPLCIA_SET_SPEC[];
extern char REPLCIA_SET_STATUS[];

class replica_set : public serializable<replica_set> {
public:
    extensions::field<std::string, REPLICA_SET_API_VERSION> api_version;
    extensions::field<std::string, REPLICA_SET_KIND> kind;
    extensions::field<object_meta, REPLICA_SET_METADATA> metadata;
    extensions::field<replica_set_spec, REPLCIA_SET_SPEC> spec;
    extensions::field<replica_set_status, REPLCIA_SET_STATUS> status;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
