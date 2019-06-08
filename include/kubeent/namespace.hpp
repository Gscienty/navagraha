#ifndef _NAVAGRAHA_KUBEENT_NAMESPACE_H
#define _NAVAGRAHA_KUBEENT_NAMESPACE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/object_meta.hpp"
#include "kubeent/namespace_spec.hpp"
#include "kubeent/namespace_status.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char NAMESPACE_API_VERSION[];
extern char NAMESPACE_KIND[];
extern char NAMESPACE_METADATA[];
extern char NAMESPACE_SPEC[];
extern char NAMESPACE_STATUS[];

class namespace_ : public extensions::serializable<namespace_> {
public:
    extensions::field<std::string, NAMESPACE_API_VERSION> api_version;
    extensions::field<std::string, NAMESPACE_KIND> kind;
    extensions::field<object_meta, NAMESPACE_METADATA> metadata;
    extensions::field<namespace_spec, NAMESPACE_SPEC> spec;
    extensions::field<namespace_status, NAMESPACE_STATUS> status;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
