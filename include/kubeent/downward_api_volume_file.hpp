#ifndef _NAVAGRAHA_KUBEENT_DOWNWARD_API_VOLUME_FILE_H
#define _NAVAGRAHA_KUBEENT_DOWNWARD_API_VOLUME_FILE_H

#include "extensions/field.hpp"
#include "kubeent/object_field_selector.hpp"
#include "kubeent/resource_field_selector.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char DOWNWARD_API_VOLUME_FILE_FIELD_REF[];
extern char DOWNWARD_API_VOLUME_FILE_MODE[];
extern char DOWNWARD_API_VOLUME_FILE_PATH[];
extern char DOWNWARD_API_VOLUME_FILE_RESOURCE_FIELD_REF[];

class downward_api_volume_file {
public:
    extensions::field<
        object_field_selector,
        DOWNWARD_API_VOLUME_FILE_FIELD_REF> field_ref;
    extensions::field<int, DOWNWARD_API_VOLUME_FILE_MODE> mode;
    extensions::field<std::string, DOWNWARD_API_VOLUME_FILE_PATH> path;
    extensions::field<
        resource_field_selector,
        DOWNWARD_API_VOLUME_FILE_RESOURCE_FIELD_REF> resource_field_ref;

    static void serialize(downward_api_volume_file & obj, std::ostringstream & str);
};

}
}

#endif
