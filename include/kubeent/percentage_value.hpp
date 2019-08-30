#ifndef _NAVAGRAHA_KUBEENT_PERCENTAGE_VALUE_H
#define _NAVAGRAHA_KUBEENT_PERCENTAGE_VALUE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"

namespace navagraha {
namespace kubeent {

extern char PERCENTAGE_VALUE[];

class percentage_value : public extensions::serializable<percentage_value> {
public:
    int value;

    void bind(extensions::serializer_helper & helper);

    percentage_value & deserialize(std::istringstream & str);

    percentage_value & serialize(std::ostringstream & str);
};

}
}

#endif
