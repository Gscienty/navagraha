#ifndef _NAVAGRAHA_KUBEENT_NAMESPACE_LIST_H
#define _NAVAGRAHA_KUBEENT_NAMESPACE_LIST_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/namespace.hpp"
#include "kubeent/list_meta.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char NAMESPACE_LIST_API_VERSION[];
extern char NAMESPACE_LIST_ITEMS[];
extern char NAMESPACE_LIST_KIND[];
extern char NAMESPACE_LIST_METADATA[];

class namespace_list : public extensions::serializable<namespace_list> {
public:
    extensions::field<std::string, NAMESPACE_LIST_API_VERSION> api_version;
    extensions::field<
        extensions::special_list<namespace_>,
        NAMESPACE_LIST_ITEMS> items;
    extensions::field<std::string, NAMESPACE_LIST_KIND> kind;
    extensions::field<list_meta, NAMESPACE_LIST_METADATA> metadata;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
