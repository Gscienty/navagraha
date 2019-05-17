#ifndef _NAVAGRAHA_DOCKERENT_IMAGE_BUILD_MSG_H
#define _NAVAGRAHA_DOCKERENT_IMAGE_BUILD_MSG_H

#include "extensions/field.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include <string>

namespace navagraha {
namespace dockerent {

extern char IMAGE_BUILD_MSG_STREAM[];

class image_build_msg : public extensions::serializable<image_build_msg> {
public:
    extensions::field<std::string, IMAGE_BUILD_MSG_STREAM> stream;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
