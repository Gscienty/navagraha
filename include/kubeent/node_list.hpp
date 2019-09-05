#ifndef _NAVAGRAHA_KUBEENT_NODE_LIST_H
#define _NAVAGRAHA_KUBEENT_NODE_LIST_H

#include "extensions/serializable.hpp"
#include "extensions/special_list.hpp"
#include "kubeent/node.hpp"
#include "kubeent/list_meta.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char NODE_LIST_API_VERSION[];
extern char NODE_LIST_ITEMS[];
extern char NODE_LIST_KIND[];
extern char NODE_LIST_METADATA[];

class node_list : public extensions::serializable<node_list> {
public:
    extensions::field<std::string, NODE_LIST_API_VERSION> api_version;
    extensions::field<extensions::special_list<node>, NODE_LIST_ITEMS> items;
    extensions::field<std::string, NODE_LIST_KIND> kind;
    extensions::field<list_meta, NODE_LIST_METADATA> metadata;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
