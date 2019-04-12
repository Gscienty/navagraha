#ifndef _NAVAGRAHA_KUBEENT_JOB_SPEC_H
#define _NAVAGRAHA_KUBEENT_JOB_SPEC_H

#include "extensions/serializer_helper.hpp"
#include "extensions/field.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/label_selector.hpp"
#include "kubeent/pod_template_spec.hpp"

namespace navagraha {
namespace kubeent {

extern char JOB_SPEC_ACTIVE_DEADLINE_SECONDS[];
extern char JOB_SPEC_BACKOFF_LIMIT[];
extern char JOB_SPEC_COMPLETIONS[];
extern char JOB_SPEC_MANUAL_SELECTOR[];
extern char JOB_SPEC_PARALLELISM[];
extern char JOB_SPEC_SELECTOR[];
extern char JOB_SPEC_TEMPLATE[];
extern char JOB_SPEC_TTL_SECONDS_AFTER_FINISHED[];

class job_spec : public serializable<job_spec> {
public:
    extensions::field<int, JOB_SPEC_ACTIVE_DEADLINE_SECONDS> active_deadline_seconds;
    extensions::field<int, JOB_SPEC_BACKOFF_LIMIT> backoff_limit;
    extensions::field<int, JOB_SPEC_COMPLETIONS> completions;
    extensions::field<bool, JOB_SPEC_MANUAL_SELECTOR> manual_selector;
    extensions::field<int, JOB_SPEC_PARALLELISM> parallelism;
    extensions::field<label_selector, JOB_SPEC_SELECTOR> selector;
    extensions::field<pod_template_spec, JOB_SPEC_TEMPLATE> template_;
    extensions::field<int, JOB_SPEC_TTL_SECONDS_AFTER_FINISHED> ttl_seconds_after_finished;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
