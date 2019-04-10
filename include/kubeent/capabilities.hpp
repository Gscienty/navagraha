#ifndef _NAVAGRAHA_KUBEENT_CAPABILITIES_H
#define _NAVAGRAHA_KUBEENT_CAPABILITIES_H

#include "extensions/field.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializer_helper.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char CAPABILITIES_ADD[];
extern char CAPABILITIES_DROP[];

class capabilities {
private:
    void bind(extensions::serializer_helper & helper);
public:
    extensions::field<
        extensions::special_list<std::string>,
        CAPABILITIES_ADD> add;
    extensions::field<
        extensions::special_list<std::string>,
        CAPABILITIES_DROP> drop;

    capabilities & serialize(std::ostringstream & str);
    capabilities & deserialize(std::istringstream & str);
    extensions::abstract_object to_abstract();
    static capabilities to_special(extensions::abstract_object & obj);

};
}
}

#endif
