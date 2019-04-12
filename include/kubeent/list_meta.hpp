#ifndef _NAVAGRAHA_KUBEENT_LIST_META_H
#define _NAVAGRAHA_KUBEENT_LIST_META_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char LIST_META_CONTINUE[];
extern char LIST_META_RESOURCE_VERSION[];
extern char LIST_META_SELF_LINK[];

class list_meta : public serializable<list_meta> {
public:
    extensions::field<std::string, LIST_META_CONTINUE> continue_;
    extensions::field<std::string, LIST_META_RESOURCE_VERSION> resource_version;
    extensions::field<std::string, LIST_META_SELF_LINK> self_link;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
