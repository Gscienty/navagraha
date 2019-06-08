#ifndef _NAVAGRAHA_KUBEENT_OBJECT_FIELD_SELECTOR_H
#define _NAVAGRAHA_KUBEENT_OBJECT_FIELD_SELECTOR_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char OBJECT_FIELD_SELECTOR_API_VERSION[];
extern char OJBECT_FIELD_SELECTOR_FIELD_PATH[];

class object_field_selector : public extensions::serializable<object_field_selector> {
public:
    extensions::field<
        std::string,
        OBJECT_FIELD_SELECTOR_API_VERSION> api_version;
    extensions::field<
        std::string,
        OJBECT_FIELD_SELECTOR_FIELD_PATH> field_path;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
