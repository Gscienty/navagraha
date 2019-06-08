#ifndef _NAVAGRAHA_KUBEENT_STATEFUL_SET_H
#define _NAVAGRAHA_KUBEENT_STATEFUL_SET_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/object_meta.hpp"
#include "kubeent/stateful_set_spec.hpp"
#include "kubeent/stateful_set_status.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char STATEFUL_SET_API_VERSION[];
extern char STATEFUL_SET_KIND[];
extern char STATEFUL_SET_METADATA[];
extern char STATEFUL_SET_SPEC[];
extern char STATEFUL_SET_STATUS[];

class stateful_set : public extensions::serializable<stateful_set> {
public:
    extensions::field<std::string, STATEFUL_SET_API_VERSION> api_version;
    extensions::field<std::string, STATEFUL_SET_KIND> kind;
    extensions::field<object_meta, STATEFUL_SET_METADATA> metadata;
    extensions::field<stateful_set_spec, STATEFUL_SET_SPEC> spec;
    extensions::field<stateful_set_status, STATEFUL_SET_STATUS> status;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
