#ifndef _NAVAGRAHA_KUBEENT_RESOURCE_FIELD_SELECTOR_H
#define _NAVAGRAHA_KUBEENT_RESOURCE_FIELD_SELECTOR_H

#include "extensions/field.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char RESOURCE_FIELD_SELECTOR_CONTAINER_NAME[];
extern char RESOURCE_FIELD_SELECTOR_DIVISOR[];
extern char RESOURCE_FIELD_SELECTOR_RESOURCE[];

class resource_field_selector {
public:
    extensions::field<
        std::string,
        RESOURCE_FIELD_SELECTOR_CONTAINER_NAME> container_name;
    extensions::field<
        std::string,
        RESOURCE_FIELD_SELECTOR_DIVISOR> divisor;
    extensions::field<
        std::string,
        RESOURCE_FIELD_SELECTOR_RESOURCE> resource;

    static void serialize(resource_field_selector & obj,
                          std::ostringstream & str);

};

}
}

#endif
