#ifndef _NAVAGRAHA_KUBEENT_POD_AFFINITY_H
#define _NAVAGRAHA_KUBEENT_POD_AFFINITY_H

#include "extensions/field.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/weighted_pod_affinity_term.hpp"
#include "kubeent/pod_affinity_term.hpp"

namespace navagraha {
namespace kubeent {

extern char POD_AFFINITY_PREFERRED_DURING_SCHEDULING_IGNORED_DURING_EXECUTION[];
extern char POD_AFFINITY_REQUIRED_DURING_SCHEDULING_IGNORED_DURING_EXECUTION[];

class pod_affinity : public extensions::serializable<pod_affinity> {
public:
    extensions::field<
        extensions::special_list<weighted_pod_affinity_term>,
        POD_AFFINITY_PREFERRED_DURING_SCHEDULING_IGNORED_DURING_EXECUTION>
            preferred_during_scheduling_ignored_during_execution;
    extensions::field<
        extensions::special_list<pod_affinity_term>,
        POD_AFFINITY_REQUIRED_DURING_SCHEDULING_IGNORED_DURING_EXECUTION>
            required_during_scheduling_ignored_during_execution;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
