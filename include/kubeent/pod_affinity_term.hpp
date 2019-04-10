#ifndef _NAVAGRAHA_KUBEENT_POD_AFFINITY_TERM_H
#define _NAVAGRAHA_KUBEENT_POD_AFFINITY_TERM_H

#include "extensions/field.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/label_selector.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char POD_AFFINITY_TERM_LABEL_SELECTOR[];
extern char POD_AFFINITY_NAMESPACES[];
extern char POD_AFFINITY_TOPOLOGY_KEY[];

class pod_affinity_term : public serializable<pod_affinity_term> {
public:
    extensions::field<
        label_selector,
        POD_AFFINITY_TERM_LABEL_SELECTOR> label_selector;
    extensions::field<
        extensions::special_list<std::string>,
        POD_AFFINITY_NAMESPACES> namespaces;
    extensions::field<
        std::string,
        POD_AFFINITY_TOPOLOGY_KEY> topology_key;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
