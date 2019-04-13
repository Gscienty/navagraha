#ifndef _NAVAGRAHA_KUBEENT_ENDPOINTS_H
#define _NAVAGRAHA_KUBEENT_ENDPOINTS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/object_meta.hpp"
#include "kubeent/endpoint_subset.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char ENDPOINTS_API_VERSION[];
extern char ENDPOINTS_KIND[];
extern char ENDPOINTS_METADATA[];
extern char ENDPOINTS_SUBSETS[];

class endpoints : public serializable<endpoints> {
public:
    extensions::field<std::string, ENDPOINTS_API_VERSION> api_version;
    extensions::field<std::string, ENDPOINTS_KIND> kind;
    extensions::field<object_meta, ENDPOINTS_METADATA> metadata;
    extensions::field<
        extensions::special_list<endpoint_subset>,
        ENDPOINTS_SUBSETS> subsets;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
