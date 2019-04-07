#ifndef _NAVAGRAHA_KUBEENT_RESOURCE_REQUIREMENTS_H
#define _NAVAGRAHA_KUBEENT_RESOURCE_REQUIREMENTS_H

#include "extensions/field.hpp"
#include "extensions/object_wrapper.hpp"

namespace navagraha {
namespace kubeent {

extern char RESOURCE_REQUIREMENTS_LIMITS[];
extern char RESOURCE_REQUIREMENTS_REQUESTS[];

class resource_requirements {
public:
    extensions::field<
        extensions::object_wrapper,
        RESOURCE_REQUIREMENTS_LIMITS> limits;

    extensions::field<
        extensions::object_wrapper,
        RESOURCE_REQUIREMENTS_REQUESTS> requests;

    static void serialize(resource_requirements & obj,
                          std::ostringstream & str);
};
}
}

#endif
