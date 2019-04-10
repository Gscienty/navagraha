#ifndef _NAVAGRAHA_KUBEENT_NODE_SELECTOR_H
#define _NAVAGRAHA_KUBEENT_NODE_SELECTOR_H

#include "extensions/field.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/node_selector_term.hpp"

namespace navagraha {
namespace kubeent {

extern char NODE_SELECTOR_NODE_SELECTOR_TERMS[];

class node_selector : public serializable<node_selector> {
public:
    extensions::field<
        extensions::special_list<node_selector_term>,
        NODE_SELECTOR_NODE_SELECTOR_TERMS> node_selector_terms;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
