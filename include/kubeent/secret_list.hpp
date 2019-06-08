#ifndef _NAVAGRAHA_KUBEENT_SECRET_LIST_H
#define _NAVAGRAHA_KUBEENT_SECRET_LIST_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/secret.hpp"
#include "kubeent/list_meta.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char SECRET_LIST_API_VERSION[];
extern char SECRET_LIST_ITEMS[];
extern char SECRET_LIST_KIND[];
extern char SECRET_LIST_METADATA[];

class secret_list : public extensions::serializable<secret_list> {
public:
    extensions::field<std::string, SECRET_API_VERSION> api_version;
    extensions::field<extensions::special_list<secret>, SECRET_LIST_ITEMS> items;
    extensions::field<std::string, SECRET_KIND> kind;
    extensions::field<object_meta, SECRET_LIST_METADATA> metadata;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
