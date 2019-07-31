#ifndef _NAVAGRAHA_KUBEENT_LIMIT_RANGE_SPEC_H
#define _NAVAGRAHA_KUBEENT_LIMIT_RANGE_SPEC_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "extensions/special_list.hpp"
#include "kubeent/limit_range_item.hpp"

namespace navagraha {
namespace kubeent {

extern char LIMIT_RANGE_SPEC_LIMITS[];

class limit_range_spec : public extensions::serializable<limit_range_spec> {
public:
    extensions::field<extensions::special_list<limit_range_item>, LIMIT_RANGE_SPEC_LIMITS> limits;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
