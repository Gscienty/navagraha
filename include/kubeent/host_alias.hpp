#ifndef _NAVAGRAHA_KUBEENT_HOST_ALIAS_H
#define _NAVAGRAHA_KUBEENT_HOST_ALIAS_H

#include "extensions/field.hpp"
#include "extensions/list_wrapper.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char HOST_ALIAS_HOSTNAMES[];
extern char HOST_ALIAS_IP[];

class host_alias {
public:
    extensions::field<
        extensions::special_list<std::string>,
        HOST_ALIAS_HOSTNAMES> hostnames;
    extensions::field<std::string, HOST_ALIAS_IP> ip;

    static void serialize(host_alias & obj, std::ostringstream & str);
};

}
}

#endif
