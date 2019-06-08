#ifndef _NAVAGRAHA_KUBEENT_NODE_H
#define _NAVAGRAHA_KUBEENT_NODE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/object_meta.hpp"
#include "kubeent/node_spec.hpp"
#include "kubeent/node_status.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char NODE_API_VERSION[];
extern char NODE_KIND[];
extern char NODE_METADATA[];
extern char NODE_SPEC[];
extern char NODE_STATUS[];

class node : public extensions::serializable<node> {
public:
    extensions::field<std::string, NODE_API_VERSION> api_version;
    extensions::field<std::string, NODE_KIND> kind;
    extensions::field<object_meta, NODE_METADATA> metadata;
    extensions::field<node_spec, NODE_SPEC> spec;
    extensions::field<node_status, NODE_STATUS> status;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
