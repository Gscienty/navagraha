#ifndef _NAVAGRAHA_KUBEENT_PERSISTENT_VOLUME_CLAIM_H
#define _NAVAGRAHA_KUBEENT_PERSISTENT_VOLUME_CLAIM_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/object_meta.hpp"
#include "kubeent/persistent_volume_claim_spec.hpp"
#include "kubeent/persistent_volume_claim_status.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char PERSISTENT_VOLUME_CLAIM_API_VERSION[];
extern char PERSISTENT_VOLUME_CLAIM_KIND[];
extern char PERSISTENT_VOLUME_CLAIM_METADATA[];
extern char PERSISTENT_VOLUME_CLAIM_SPEC[];
extern char PERSISTENT_VOLUME_CLAIM_STATUS[];

class persistent_volume_claim : public serializable<persistent_volume_claim> {
public:
    extensions::field<std::string, PERSISTENT_VOLUME_CLAIM_API_VERSION> api_version;
    extensions::field<std::string, PERSISTENT_VOLUME_CLAIM_KIND> kind;
    extensions::field<object_meta, PERSISTENT_VOLUME_CLAIM_METADATA> metadata;
    extensions::field<persistent_volume_claim_spec, PERSISTENT_VOLUME_CLAIM_SPEC> spec;
    extensions::field<persistent_volume_claim_status, PERSISTENT_VOLUME_CLAIM_STATUS> status;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
