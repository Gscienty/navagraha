#ifndef _NAVAGRAHA_KUBEENT_NODE_AFFINITY_H
#define _NAVAGRAHA_KUBEENT_NODE_AFFINITY_H

#include "extensions/field.hpp"
#include "extensions/list_wrapper.hpp"
#include "kubeent/preferred_scheduling_term.hpp"
#include "kubeent/node_selector.hpp"

namespace navagraha {
namespace kubeent {

extern char NODE_AFFINITY_PREFERRED_DURING_SCHEDULING_IGNORED_DURING_EXECUTION[];
extern char NODE_AFFINITY_REQUIRED_DURING_SCHEDULING_IGNORED_DURING_EXECUTION[];

class node_affinity {
public:
    extensions::field<
        extensions::special_list<preferred_scheduling_term>,
        NODE_AFFINITY_PREFERRED_DURING_SCHEDULING_IGNORED_DURING_EXECUTION>
            preferred_during_scheduling_ignored_during_execution;
    extensions::field<
        node_selector,
        NODE_AFFINITY_REQUIRED_DURING_SCHEDULING_IGNORED_DURING_EXECUTION>
            required_during_scheduling_ignored_during_execution;

    static void serialize(node_affinity & obj, std::ostringstream & str);
};

}
}

#endif
