#ifndef _NAVAGRAHA_KUBEENT_JOB_TEMPLATE_SPEC_H
#define _NAVAGRAHA_KUBEENT_JOB_TEMPLATE_SPEC_H

#include "extensions/serializer_helper.hpp"
#include "extensions/field.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/object_meta.hpp"
#include "kubeent/job_spec.hpp"

namespace navagraha {
namespace kubeent {

extern char JOB_TEMPLATE_SPEC_METADATA[];
extern char JOB_TEMPLATE_SPEC_SPEC[];

class job_template_spec : public serializable<job_template_spec> {
public:
    extensions::field<object_meta, JOB_TEMPLATE_SPEC_METADATA> metadata;
    extensions::field<job_spec, JOB_TEMPLATE_SPEC_SPEC> spec;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
