#ifndef _NAVAGRAHA_KUBEENT_NAMESPACE_SPEC_H
#define _NAVAGRAHA_KUBEENT_NAMESPACE_SPEC_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "kubeent/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char NAMESPACE_SPEC_FINALIZERS[];

class namespace_spec : public serializable<namespace_spec> {
public:
    extensions::field<
        extensions::special_list<std::string>,
        NAMESPACE_SPEC_FINALIZERS> finalizers;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
