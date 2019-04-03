#ifndef _NAVAGRAHA_KUBEENT_DOWNWARD_API_VOLUME_SOURCE_H
#define _NAVAGRAHA_KUBEENT_DOWNWARD_API_VOLUME_SOURCE_H

#include "extensions/field.hpp"
#include "kubeent/downward_api_volume_file.hpp"

namespace navagraha {
namespace kubeent {

extern char DOWNWARD_API_VOLUME_SOURCE_DEFAULT_MODE[];
extern char DOWNWARD_API_VOLUME_SOURCE_ITEMS[];

class downward_api_volume_source {
public:
    extensions::field<int, DOWNWARD_API_VOLUME_SOURCE_DEFAULT_MODE> default_mode;
    extensions::field<downward_api_volume_file, DOWNWARD_API_VOLUME_SOURCE_ITEMS> items;

    static void serialize(downward_api_volume_source & obj, std::ostringstream & str);
};

}
}

#endif
