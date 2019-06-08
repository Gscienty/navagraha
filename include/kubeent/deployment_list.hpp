#ifndef _NAVAGRAHA_KUBEENT_DEPLOYMENT_LIST_H
#define _NAVAGRAHA_KUBEENT_DEPLOYMENT_LIST_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/deployment.hpp"
#include "kubeent/list_meta.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char DEPLOYMENT_LIST_API_VERSION[];
extern char DEPLOYMENT_LIST_ITEMS[];
extern char DEPLOYMENT_LIST_KIND[];
extern char DEPLOYMENT_LIST_METADATA[];

class deployment_list : public extensions::serializable<deployment_list> {
public:
    extensions::field<std::string, DEPLOYMENT_LIST_API_VERSION> api_version;
    extensions::field<
        extensions::special_list<deployment>, DEPLOYMENT_LIST_ITEMS> items;
    extensions::field<std::string, DEPLOYMENT_LIST_KIND> kind;
    extensions::field<list_meta, DEPLOYMENT_LIST_METADATA> metadata;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
