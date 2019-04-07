#ifndef _NAVAGRAHA_KUBEENT_EMPTY_DIR_VOLUME_SOURCE_H
#define _NAVAGRAHA_KUBEENT_EMPTY_DIR_VOLUME_SOURCE_H

#include "extensions/field.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char EMPTY_DIR_VOLUME_SOURCE_MEDIUM[];
extern char EMPTY_DIR_VOLUME_SOURCE_SIZE_LIMIT[];

class empty_dir_volume_source {
public:
    extensions::field<std::string, EMPTY_DIR_VOLUME_SOURCE_MEDIUM> medium;
    extensions::field<std::string, EMPTY_DIR_VOLUME_SOURCE_SIZE_LIMIT> size_limit;

    static void serialize(empty_dir_volume_source & obj, std::ostringstream & str);
};

}
}

#endif
