#ifndef _NAVAGRAHA_KUBEENT_INGRESS_SPEC_H
#define _NAVAGRAHA_KUBEENT_INGRESS_SPEC_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/ingress_backend.hpp"
#include "kubeent/ingress_rule.hpp"
#include "kubeent/ingress_tls.hpp"

namespace navagraha {
namespace kubeent {

extern char INGRESS_SPEC_BACKEND[];
extern char INGRESS_SPEC_RULES[];
extern char INGRESS_SPEC_TLS[];

class ingress_spec : public serializable<ingress_spec> {
public:
    extensions::field<ingress_backend, INGRESS_SPEC_BACKEND> backend;
    extensions::field<
        extensions::special_list<ingress_rule>,
        INGRESS_SPEC_RULES> rules;
    extensions::field<
        extensions::special_list<ingress_tls>,
        INGRESS_SPEC_TLS> tls;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
