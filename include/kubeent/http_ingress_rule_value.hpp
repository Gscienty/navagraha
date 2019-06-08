#ifndef _NAVAGRAHA_KUBEENT_HTTP_INGRESS_RULE_VALUE_H
#define _NAVAGRAHA_KUBEENT_HTTP_INGRESS_RULE_VALUE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/http_ingress_path.hpp"

namespace navagraha {
namespace kubeent {

extern char HTTP_INGRESS_RULE_VALUE_PATHS[];

class http_ingress_rule_value : public extensions::serializable<http_ingress_rule_value> {
public:
    extensions::field<
        extensions::special_list<http_ingress_path>,
        HTTP_INGRESS_RULE_VALUE_PATHS> paths;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
