#ifndef _NAVAGRAHA_KUBEENT_DEPLOYMENT_H
#define _NAVAGRAHA_KUBEENT_DEPLOYMENT_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/object_meta.hpp"
#include "kubeent/deployment_spec.hpp"
#include "kubeent/deployment_status.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char DEPLOYMENT_API_VERSION[];
extern char DEPLOYMENT_KIND[];
extern char DEPLOYMENT_METADATA[];
extern char DEPLOYMENT_SPEC[];
extern char DEPLOYMENT_STATUS[];

class deployment : public extensions::serializable<deployment> {
public:
    extensions::field<std::string, DEPLOYMENT_API_VERSION> api_version;
    extensions::field<std::string, DEPLOYMENT_KIND> kind;
    extensions::field<object_meta, DEPLOYMENT_METADATA> metadata;
    extensions::field<deployment_spec, DEPLOYMENT_SPEC> spec;
    extensions::field<deployment_status, DEPLOYMENT_STATUS> status;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
