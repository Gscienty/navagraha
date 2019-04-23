#ifndef _NAVAGRAHA_KUBEENT_DAEMON_SET_LIST_H
#define _NAVAGRAHA_KUBEENT_DAEMON_SET_LIST_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "kubeent/daemon_set.hpp"
#include "kubeent/list_meta.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char DAEMON_SET_LIST_API_VERSION[];
extern char DAEMON_SET_LIST_ITEMS[];
extern char DAEMON_SET_LIST_KIND[];
extern char DAEMON_SET_LIST_METADATA[];

class daemon_set_list : public serializable<daemon_set_list> {
public:
    extensions::field<std::string, DAEMON_SET_LIST_API_VERSION> api_version;
    extensions::field<
        extensions::special_list<daemon_set>, DAEMON_SET_LIST_ITEMS> items;
    extensions::field<std::string, DAEMON_SET_LIST_KIND> kind;
    extensions::field<list_meta, DAEMON_SET_LIST_METADATA> metadata;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
