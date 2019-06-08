#ifndef _NAVAGRAHA_KUBEENT_CONTAINER_IMAGE_H
#define _NAVAGRAHA_KUBEENT_CONTAINER_IMAGE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char CONTAINER_IMAGE_NAMES[];
extern char CONTAINER_IMAGE_SIZE_BYTES[];

class container_image : public extensions::serializable<container_image> {
public:
    extensions::field<
        extensions::special_list<std::string>,
        CONTAINER_IMAGE_NAMES> names;
    extensions::field<int, CONTAINER_IMAGE_SIZE_BYTES> size_bytes;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
