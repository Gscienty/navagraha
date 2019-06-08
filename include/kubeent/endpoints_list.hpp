#ifndef _NAVAGRAHA_KUBEENT_ENDPOINTS_LIST_H
#define _NAVAGRAHA_KUBEENT_ENDPOINTS_LIST_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "kubeent/endpoints.hpp"
#include "kubeent/list_meta.hpp"

namespace navagraha {
namespace kubeent {

extern char ENDPOINTS_LIST_API_VERSION[];
extern char ENDPOINTS_LIST_ITEMS[];
extern char ENDPOINTS_LIST_KIND[];
extern char ENDPOINTS_LIST_METADATA[];

class endpoints_list : public extensions::serializable<endpoints_list> {
public:
    extensions::field<std::string, ENDPOINTS_API_VERSION> api_version;
    extensions::field<
        extensions::special_list<endpoints>, ENDPOINTS_LIST_ITEMS> items;
    extensions::field<std::string, ENDPOINTS_LIST_KIND> kind;
    extensions::field<list_meta, ENDPOINTS_LIST_METADATA> metadata;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
