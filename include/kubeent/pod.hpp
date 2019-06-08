#ifndef _NAVAGRAHA_KUBEENT_POD_H
#define _NAVAGRAHA_KUBEENT_POD_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/object_meta.hpp"
#include "kubeent/pod_spec.hpp"
#include "kubeent/pod_status.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char POD_API_VERSION[];
extern char POD_KIND[];
extern char POD_METADATA[];
extern char POD_SPEC[];
extern char POD_STATUS[];

class pod : public extensions::serializable<pod> {
public:
    extensions::field<std::string, POD_API_VERSION> api_version;
    extensions::field<std::string, POD_KIND> kind;
    extensions::field<object_meta, POD_METADATA> metadata;
    extensions::field<pod_spec, POD_SPEC> spec;
    extensions::field<pod_status, POD_STATUS> status;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
