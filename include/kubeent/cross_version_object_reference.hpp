#ifndef _NAVAGRAHA_KUBEENT_CROSS_VERSION_OBJECT_REFERENCE_H
#define _NAVAGRAHA_KUBEENT_CROSS_VERSION_OBJECT_REFERENCE_H

#include "extensions/serializable.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/field.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char CROSS_VERSION_OBJECT_REFERENCE_API_VERSION[];
extern char CROSS_VERSION_OBJECT_REFERENCE_KIND[];
extern char CROSS_VERSION_OBJECT_REFERENCE_NAME[];

class cross_version_object_reference : public extensions::serializable<cross_version_object_reference> {
public:
    extensions::field<std::string, CROSS_VERSION_OBJECT_REFERENCE_API_VERSION> api_version;
    extensions::field<std::string, CROSS_VERSION_OBJECT_REFERENCE_KIND> kind;
    extensions::field<std::string, CROSS_VERSION_OBJECT_REFERENCE_NAME> name;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
