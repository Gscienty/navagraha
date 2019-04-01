#ifndef _NAVAGRAHA_KUBEENT_PREFERED_SCHEDULING_TERM_H
#define _NAVAGRAHA_KUBEENT_PREFERED_SCHEDULING_TERM_H

#include "extensions/field.hpp"
#include "kubeent/node_selector_term.hpp"

namespace navagraha {
namespace kubeent {

extern char PREFERED_SCHEDULING_TERM_PERFERENCE[];
extern char PREFERED_SCHEDULING_TERM_WEIGHT[];

class prefered_scheduling_term {
public:
    extensions::field<
        node_selector_term,
        PREFERED_SCHEDULING_TERM_PERFERENCE> perference;
    extensions::field<
        int,
        PREFERED_SCHEDULING_TERM_WEIGHT> weight;

    static void serialize(prefered_scheduling_term & obj,
                          std::ostringstream & str);
};

}
}

#endif
