#ifndef _NAVAGRAHA_KUBEENT_LIMIT_RANGE_H
#define _NAVAGRAHA_KUBEENT_LIMIT_RANGE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/limit_range_spec.hpp"
#include "kubeent/object_meta.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char LIMIT_RANGE_API_VERSION[];
extern char LIMIT_RANGE_KIND[];
extern char LIMIT_RANGE_METADATA[];
extern char LIMIT_RANGE_SPEC[];

class limit_range : public extensions::serializable<limit_range> {
public:
    extensions::field<std::string, LIMIT_RANGE_API_VERSION> api_version;
    extensions::field<std::string, LIMIT_RANGE_KIND> kind;
    extensions::field<object_meta, LIMIT_RANGE_METADATA> metadata;
    extensions::field<limit_range_spec, LIMIT_RANGE_SPEC> spec;

    void bind(extensions::serializer_helper & helper);
};

}
}


#endif
