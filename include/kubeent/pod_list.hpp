#ifndef _NAVAGRAHA_KUBEENT_POD_LIST_H
#define _NAVAGRAHA_KUBEENT_POD_LIST_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "extensions/special_list.hpp"
#include "kubeent/list_meta.hpp"
#include "kubeent/pod.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char POD_LIST_API_VERSION[];
extern char POD_LIST_KIND[];
extern char POD_LIST_ITEMS[];
extern char POD_LIST_METADATA[];

class pod_list : public extensions::serializable<pod_list> {
public:
    extensions::field<std::string, POD_LIST_API_VERSION> api_version;
    extensions::field<std::string, POD_LIST_KIND> kind;
    extensions::field<list_meta, POD_LIST_METADATA> metadata;
    extensions::field<extensions::special_list<pod>, POD_LIST_ITEMS> items;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
