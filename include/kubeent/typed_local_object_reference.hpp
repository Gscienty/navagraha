#ifndef _NAVAGRAHA_KUBEENT_TYPED_LOCAL_OBJECT_REFERENCE_H
#define _NAVAGRAHA_KUBEENT_TYPED_LOCAL_OBJECT_REFERENCE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char TYPED_LOCAL_OBJECT_REFERENCE_API_GROUP[];
extern char TYPED_LOCAL_OBJECT_REFERENCE_KIND[];
extern char TYPED_LOCAL_OBJECT_REFERENCE_NAME[];

class typed_local_object_reference : public extensions::serializable<typed_local_object_reference> {
public:
    extensions::field<std::string, TYPED_LOCAL_OBJECT_REFERENCE_API_GROUP> api_group;
    extensions::field<std::string, TYPED_LOCAL_OBJECT_REFERENCE_KIND> kind;
    extensions::field<std::string, TYPED_LOCAL_OBJECT_REFERENCE_NAME> name;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
