#ifndef _NAVAGRAHA_KUBEENT_DOWNWARD_API_VOLUME_SOURCE_H
#define _NAVAGRAHA_KUBEENT_DOWNWARD_API_VOLUME_SOURCE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/downward_api_volume_file.hpp"
#include "kubeent/serializable.hpp"

namespace navagraha {
namespace kubeent {

extern char DOWNWARD_API_VOLUME_SOURCE_DEFAULT_MODE[];
extern char DOWNWARD_API_VOLUME_SOURCE_ITEMS[];

class downward_api_volume_source : public serializable<downward_api_volume_source> {
public:
    extensions::field<int, DOWNWARD_API_VOLUME_SOURCE_DEFAULT_MODE> default_mode;
    extensions::field<downward_api_volume_file, DOWNWARD_API_VOLUME_SOURCE_ITEMS> items;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
