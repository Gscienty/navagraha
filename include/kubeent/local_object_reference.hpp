#ifndef _NAVAGRAHA_KUBEENT_LOCAL_OBJECT_REFERENCE_H
#define _NAVAGRAHA_KUBEENT_LOCAL_OBJECT_REFERENCE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char LOCAL_OBJECT_REFERENCE_NAME[];

class local_object_reference : public serializable<local_object_reference> {
public:
    extensions::field<std::string, LOCAL_OBJECT_REFERENCE_NAME> name;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
