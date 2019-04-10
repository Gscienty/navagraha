#ifndef _NAVAGRAHA_KUBEENT_RESOURCE_REQUIREMENTS_H
#define _NAVAGRAHA_KUBEENT_RESOURCE_REQUIREMENTS_H

#include "extensions/field.hpp"
#include "extensions/common_object.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"

namespace navagraha {
namespace kubeent {

extern char RESOURCE_REQUIREMENTS_LIMITS[];
extern char RESOURCE_REQUIREMENTS_REQUESTS[];

class resource_requirements : public serializable<resource_requirements> {
public:
    extensions::field<
        extensions::common_object,
        RESOURCE_REQUIREMENTS_LIMITS> limits;

    extensions::field<
        extensions::common_object,
        RESOURCE_REQUIREMENTS_REQUESTS> requests;

    void bind(extensions::serializer_helper & helper);
};
}
}

#endif
