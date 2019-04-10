#ifndef _NAVAGRAHA_KUBEENT_LABEL_SELECTOR_H
#define _NAVAGRAHA_KUBEENT_LABEL_SELECTOR_H

#include "extensions/field.hpp"
#include "extensions/special_list.hpp"
#include "extensions/common_object.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/label_selector_requirement.hpp"

namespace navagraha {
namespace kubeent {

extern char LABEL_SELECTOR_MATCH_EXPRESSIONS[];
extern char LABEL_SELECTOR_MATCH_LABELS[];

class label_selector : public serializable<label_selector> {
public:
    extensions::field<
        extensions::special_list<label_selector_requirement>,
        LABEL_SELECTOR_MATCH_EXPRESSIONS> match_expressions;
    extensions::field<
        extensions::common_object,
        LABEL_SELECTOR_MATCH_LABELS> match_labels;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
