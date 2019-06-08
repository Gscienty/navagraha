#ifndef _NAVAGRAHA_KUBEENT_SERVICE_LIST_H
#define _NAVAGRAHA_KUBEENT_SERVICE_LIST_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/service.hpp"
#include "kubeent/list_meta.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char SERVICE_LIST_API_VERSION[];
extern char SERVICE_LIST_ITEMS[];
extern char SERVICE_LIST_KIND[];
extern char SERVICE_LIST_METADATA[];

class service_list : public extensions::serializable<service_list> {
public:
    extensions::field<std::string, SERVICE_LIST_API_VERSION> api_version;
    extensions::field<
        extensions::special_list<service>, SERVICE_LIST_ITEMS> items;
    extensions::field<std::string, SERVICE_LIST_KIND> kind;
    extensions::field<list_meta, SERVICE_LIST_METADATA> metadata;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
