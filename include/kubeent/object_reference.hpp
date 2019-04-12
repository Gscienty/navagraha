#ifndef _NAVAGRAHA_KUBEENT_OBJECT_REFERENCE_H
#define _NAVAGRAHA_KUBEENT_OBJECT_REFERENCE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char OBJECT_REFERENCE_API_VERSION[];
extern char OBJECT_REFERENCE_FIELD_PATH[];
extern char OBJECT_REFERENCE_KIND[];
extern char OBJECT_REFERENCE_NAME[];
extern char OBJECT_REFERENCE_NAMESPACE[];
extern char OBJECT_REFERENCE_RESOURCE_VERSION[];
extern char OBJECT_REFERENCE_UID[];

class object_reference : public serializable<object_reference> {
public:
    extensions::field<std::string, OBJECT_REFERENCE_API_VERSION> api_version;
    extensions::field<std::string, OBJECT_REFERENCE_FIELD_PATH> field_path;
    extensions::field<std::string, OBJECT_REFERENCE_KIND> kind;
    extensions::field<std::string, OBJECT_REFERENCE_NAME> name;
    extensions::field<std::string, OBJECT_REFERENCE_NAMESPACE> namespace_;
    extensions::field<std::string, OBJECT_REFERENCE_RESOURCE_VERSION> resource_version;
    extensions::field<std::string, OBJECT_REFERENCE_UID> uid;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
