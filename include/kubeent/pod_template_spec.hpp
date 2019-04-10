#ifndef _NAVAGRAHA_KUBEENT_POD_TEMPLATE_SPEC_H
#define _NAVAGRAHA_KUBEENT_POD_TEMPLATE_SPEC_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/object_meta.hpp"
#include "kubeent/pod_spec.hpp"

namespace navagraha {
namespace kubeent {

extern char POD_TEMPLATE_SPEC_METADATA[];
extern char POD_TEMPLATE_SPEC_SPEC[];

class pod_template_spec : public serializable<pod_template_spec> {
public:
    extensions::field<object_meta, POD_TEMPLATE_SPEC_METADATA> metadata;
    extensions::field<pod_spec, POD_TEMPLATE_SPEC_SPEC> spec;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
