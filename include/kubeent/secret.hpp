#ifndef _NAVAGRAHA_KUBEENT_SECRET_H
#define _NAVAGRAHA_KUBEENT_SECRET_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/common_object.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/object_meta.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char SECRET_API_VERSION[];
extern char SECRET_DATA[];
extern char SECRET_KIND[];
extern char SECRET_METADATA[];
extern char SECRET_STRING_DATA[];
extern char SECRET_TYPE[];

class secret : public serializable<secret> {
public:
    extensions::field<std::string, SECRET_API_VERSION> api_version;
    extensions::field<extensions::common_object, SECRET_DATA> data;
    extensions::field<std::string, SECRET_KIND> kind;
    extensions::field<object_meta, SECRET_METADATA> metadata;
    extensions::field<extensions::common_object, SECRET_STRING_DATA> string_data;
    extensions::field<std::string, SECRET_TYPE> type;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
