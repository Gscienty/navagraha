#ifndef _NAVAGRAHA_KUBEENT_DEPLOYMENT_SPEC_H
#define _NAVAGRAHA_KUBEENT_DEPLOYMENT_SPEC_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/label_selector.hpp"
#include "kubeent/deployment_strategy.hpp"
#include "kubeent/pod_template_spec.hpp"

namespace navagraha {
namespace kubeent {

extern char DEPLOYMENT_SPEC_MIN_READY_SECONDS[];
extern char DEPLOYMENT_SPCE_PAUSED[];
extern char DEPLOYMENT_SPEC_PROGRESS_DEADLINE_SECONDS[];
extern char DEPLOYMENT_SPEC_REPLICAS[];
extern char DEPLOYMENT_SPEC_REVISION_HISTORY_LIMIT[];
extern char DEPOLYMENT_SPEC_SELECTOR[];
extern char DEPLOYMENT_SPEC_STRATEGY[];
extern char DEPLOYMENT_SPEC_TEMPLATE[];

class deployment_spec : public extensions::serializable<deployment_spec> {
public:
    extensions::field<int, DEPLOYMENT_SPEC_MIN_READY_SECONDS> min_ready_seconds;
    extensions::field<bool, DEPLOYMENT_SPCE_PAUSED> paused;
    extensions::field<int, DEPLOYMENT_SPEC_PROGRESS_DEADLINE_SECONDS> progress_deadline_seconds;
    extensions::field<int, DEPLOYMENT_SPEC_REPLICAS> replicas;
    extensions::field<int, DEPLOYMENT_SPEC_REVISION_HISTORY_LIMIT> revision_history_limit;
    extensions::field<label_selector, DEPOLYMENT_SPEC_SELECTOR> selector;
    extensions::field<deployment_strategy, DEPLOYMENT_SPEC_STRATEGY> strategy;
    extensions::field<pod_template_spec, DEPLOYMENT_SPEC_TEMPLATE> template_;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
