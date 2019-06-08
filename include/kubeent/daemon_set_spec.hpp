#ifndef _NAVAGRAHA_KUBEENT_DAEMON_SET_SPEC_H
#define _NAVAGRAHA_KUBEENT_DAEMON_SET_SPEC_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/label_selector.hpp"
#include "kubeent/pod_template_spec.hpp"
#include "kubeent/daemon_set_update_strategy.hpp"

namespace navagraha {
namespace kubeent {

extern char DAEMON_SET_SPEC_MIN_READY_SECONDS[];
extern char DAEMON_SET_SPEC_REVISION_HISTORY_LIMIT[];
extern char DAEMON_SET_SPEC_SELECTOR[];
extern char DAEMON_SET_SPEC_TEMPLATE[];
extern char DAEMON_SET_SPEC_UPDATE_STRATEGY[];

class daemon_set_spec : public extensions::serializable<daemon_set_spec> {
public:
    extensions::field<int, DAEMON_SET_SPEC_MIN_READY_SECONDS> min_ready_seconds;
    extensions::field<int, DAEMON_SET_SPEC_REVISION_HISTORY_LIMIT> revision_history_limit;
    extensions::field<label_selector, DAEMON_SET_SPEC_SELECTOR> selector;
    extensions::field<pod_template_spec, DAEMON_SET_SPEC_TEMPLATE> template_;
    extensions::field<daemon_set_update_strategy, DAEMON_SET_SPEC_UPDATE_STRATEGY> update_strategy;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
