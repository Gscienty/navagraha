#ifndef _NAVAGRAHA_DOCKERENT_IMAGE_H
#define _NAVAGRAHA_DOCKERENT_IMAGE_H

#include "extensions/field.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include <string>

namespace navagraha {
namespace dockerent {

extern char IMAGE_ID[];
extern char IMAGE_PARENT_ID[];
extern char IMAGE_REPO_TAGS[];
extern char IMAGE_REPO_DIGESTS[];
extern char IMAGE_CREATED[];
extern char IMAGE_SIZE[];
extern char IMAGE_SHARED_SIZE[];
extern char IMAGE_VIRTUAL_SIZE[];
extern char IMAGE_LABELS[];
extern char IMAGE_CONTAINERS[];

class image : public extensions::serializable<image> {
public:
    extensions::field<std::string, IMAGE_ID> id;
    extensions::field<std::string, IMAGE_PARENT_ID> parent_id;
    extensions::field<extensions::special_list<std::string>, IMAGE_REPO_TAGS> repo_tags;
    extensions::field<extensions::special_list<std::string>, IMAGE_REPO_DIGESTS> repo_digests;
    extensions::field<int, IMAGE_CREATED> created;
    extensions::field<int, IMAGE_SIZE> size;
    extensions::field<int, IMAGE_SHARED_SIZE> shared_size;
    extensions::field<int, IMAGE_VIRTUAL_SIZE> virtual_size;
    extensions::field<extensions::common_object, IMAGE_LABELS> labels;
    extensions::field<int, IMAGE_CONTAINERS> containers;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
