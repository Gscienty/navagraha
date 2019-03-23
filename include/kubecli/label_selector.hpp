#ifndef _NAVAGRAHA_KUBECTL_LABEL_SELECTOR_H
#define _NAVAGRAHA_KUBECTL_LABEL_SELECTOR_H

#include "extensions/field.hpp"
#include "extensions/list_wrapper.hpp"
#include "extensions/object_wrapper.hpp"
#include "kubecli/label_selector_requirement.hpp"

namespace navagraha {
namespace kubectl {

extern char LABEL_SELECTOR_MATCH_EXPRESSIONS[];
extern char LABEL_SELECTOR_MATCH_LABELS[];

class label_selector {
public:
    extensions::field<
        extensions::special_list<label_selector_requirement>,
        LABEL_SELECTOR_MATCH_EXPRESSIONS> match_expressions;
    extensions::field<
        extensions::object_wrapper,
        LABEL_SELECTOR_MATCH_LABELS> match_labels;

    static void serialize(label_selector & obj, std::ostringstream & str);
};

}
}

#endif
