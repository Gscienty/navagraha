#ifndef _NAVAGRAHA_KUBEENT_CONFIG_MAP_H
#define _NAVAGRAHA_KUBEENT_CONFIG_MAP_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/common_object.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/object_meta.hpp"

namespace navagraha {
namespace kubeent {

extern char CONFIG_MAP_API_VERSION[];
extern char CONFIG_MAP_BINARY_DATA[];
extern char CONFIG_MAP_DATA[];
extern char CONFIG_MAP_KIND[];
extern char CONFIG_MAP_METADATA[];

class config_map : public extensions::serializable<config_map> {
public:
    extensions::field<std::string, CONFIG_MAP_API_VERSION> api_version;
    extensions::field<extensions::common_object, CONFIG_MAP_BINARY_DATA> binary_data;
    extensions::field<extensions::common_object, CONFIG_MAP_DATA> data;
    extensions::field<std::string, CONFIG_MAP_KIND> kind;
    extensions::field<object_meta, CONFIG_MAP_METADATA> metadata;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
