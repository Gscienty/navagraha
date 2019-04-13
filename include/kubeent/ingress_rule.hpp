#ifndef _NAVAGRAHA_KUBEENT_INGRESS_RULE_H
#define _NAVAGRAHA_KUBEENT_INGRESS_RULE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/http_ingress_rule_value.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char INGRESS_RULE_HOST[];
extern char INGRESS_RULE_HTTP[];

class ingress_rule : public serializable<ingress_rule> {
public:
    extensions::field<std::string, INGRESS_RULE_HOST> host;
    extensions::field<http_ingress_rule_value, INGRESS_RULE_HTTP> http;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
