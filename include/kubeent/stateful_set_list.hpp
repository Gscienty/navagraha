#ifndef _NAVAGRAHA_KUBEENT_STATEFUL_SET_LIST_H
#define _NAVAGRAHA_KUBEENT_STATEFUL_SET_LIST_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/stateful_set.hpp"
#include "kubeent/list_meta.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char STATEFUL_SET_LIST_API_VERSION[];
extern char STATEFUL_SET_LIST_ITEMS[];
extern char STATEFUL_SET_LIST_KIND[];
extern char STATEFUL_SET_LIST_METADATA[];

class stateful_set_list : public extensions::serializable<stateful_set_list> {
public:
    extensions::field<std::string, STATEFUL_SET_LIST_API_VERSION> api_version;
    extensions::field<extensions::special_list<stateful_set>, STATEFUL_SET_LIST_ITEMS> items;
    extensions::field<std::string, STATEFUL_SET_LIST_KIND> kind;
    extensions::field<object_meta, STATEFUL_SET_LIST_METADATA> metadata;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
