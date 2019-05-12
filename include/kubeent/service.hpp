#ifndef _NAVAGRAHA_KUBEENT_SERVICE_H
#define _NAVAGRAHA_KUBEENT_SERVICE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/object_meta.hpp"
#include "kubeent/service_spec.hpp"
#include "kubeent/service_status.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char SERVICE_API_VERSION[];
extern char SERVICE_KIND[];
extern char SERVICE_METADATA[];
extern char SERVICE_SPEC[];
extern char SERVICE_STATUS[];

class service : public serializable<service> {
public:
    extensions::field<std::string, SERVICE_API_VERSION> api_version;
    extensions::field<std::string, SERVICE_KIND> kind;
    extensions::field<object_meta, SERVICE_METADATA> metadata;
    extensions::field<service_spec, SERVICE_SPEC> spec;
    extensions::field<service_status, SERVICE_STATUS> status;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
