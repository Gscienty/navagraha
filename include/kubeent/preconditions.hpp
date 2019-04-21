#ifndef _NAVAGRAHA_KUBEENT_PRECONDITIONS_H
#define _NAVAGRAHA_KUBEENT_PRECONDITIONS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char PRECONDITIONS_UID[];

class preconditions : public serializable<preconditions> {
public:
    extensions::field<std::string, PRECONDITIONS_UID> uid;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
