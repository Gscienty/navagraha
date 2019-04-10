#ifndef _NAVAGRAHA_KUBEENT_PREFERRED_SCHEDULING_TERM_H
#define _NAVAGRAHA_KUBEENT_PREFERRED_SCHEDULING_TERM_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/node_selector_term.hpp"

namespace navagraha {
namespace kubeent {

extern char PREFERRED_SCHEDULING_TERM_PREFERENCE[];
extern char PREFERRED_SCHEDULING_TERM_WEIGHT[];

class preferred_scheduling_term : public serializable<preferred_scheduling_term> {
public:
    extensions::field<
        node_selector_term,
        PREFERRED_SCHEDULING_TERM_PREFERENCE> perference;
    extensions::field<
        int,
        PREFERRED_SCHEDULING_TERM_WEIGHT> weight;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
