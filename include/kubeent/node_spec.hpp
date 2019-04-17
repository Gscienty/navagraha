#ifndef _NAVAGRAHA_KUBEENT_NODE_SPEC_H
#define _NAVAGRAHA_KUBEENT_NODE_SPEC_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/node_config_source.hpp"
#include "kubeent/taint.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char NODE_SPEC_CONFIG_SOURCE[];
extern char NODE_SPEC_EXTERNAL_ID[];
extern char NODE_SPEC_POD_CIDR[];
extern char NODE_SPEC_PROVIDER_ID[];
extern char NODE_SPEC_TAINTS[];
extern char NODE_SPEC_UNSCHEDULABLE[];

class node_spec : public serializable<node_spec> {
public:
    extensions::field<node_config_source, NODE_SPEC_CONFIG_SOURCE> config_source;
    extensions::field<std::string, NODE_SPEC_EXTERNAL_ID> external_id;
    extensions::field<std::string, NODE_SPEC_POD_CIDR> pod_cidr;
    extensions::field<std::string, NODE_SPEC_PROVIDER_ID> provider_id;
    extensions::field<
        extensions::special_list<taint>, NODE_SPEC_TAINTS> taints;
    extensions::field<bool, NODE_SPEC_UNSCHEDULABLE> unschedulable;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
