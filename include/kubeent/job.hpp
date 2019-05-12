#ifndef _NAVAGRAHA_KUBEENT_JOB_H
#define _NAVAGRAHA_KUBEENT_JOB_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/object_meta.hpp"
#include "kubeent/job_spec.hpp"
#include "kubeent/job_status.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char JOB_API_VERSION[];
extern char JOB_KIND[];
extern char JOB_METADATA[];
extern char JOB_SPEC[];
extern char JOB_STATUS[];

class job : public serializable<job> {
public:
    extensions::field<std::string, JOB_API_VERSION> api_version;
    extensions::field<std::string, JOB_KIND> kind;
    extensions::field<object_meta, JOB_METADATA> metadata;
    extensions::field<job_spec, JOB_SPEC> spec;
    extensions::field<job_status, JOB_STATUS> status;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
