#ifndef _NAVAGRAHA_KUBEENT_INITIALIZERS_H
#define _NAVAGRAHA_KUBEENT_INITIALIZERS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/initializer.hpp"
#include <sstream>

namespace navagraha {
namespace kubeent {

extern char INITIALIZERS_PENDING[];

class initializers : public extensions::serializable<initializers> {
public:
    extensions::field<extensions::special_list<initializer>, INITIALIZERS_PENDING> pending;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
