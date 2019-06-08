#ifndef _NAVAGRAHA_KUBEENT_INGRESS_H
#define _NAVAGRAHA_KUBEENT_INGRESS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/object_meta.hpp"
#include "kubeent/ingress_spec.hpp"
#include "kubeent/ingress_status.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char INGRESS_API_VERSION[];
extern char INGRESS_KIND[];
extern char INGRESS_METADATA[];
extern char INGRESS_SPEC[];
extern char INGRESS_STATUS[];

class ingress : public extensions::serializable<ingress> {
public:
    extensions::field<std::string, INGRESS_API_VERSION> api_version;
    extensions::field<std::string, INGRESS_KIND> kind;
    extensions::field<object_meta, INGRESS_METADATA> metadata;
    extensions::field<ingress_spec, INGRESS_SPEC> spec;
    extensions::field<ingress_status, INGRESS_STATUS> status;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
