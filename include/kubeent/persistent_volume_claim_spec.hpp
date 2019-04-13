#ifndef _NAVAGRAHA_KUBEENT_PERSISTENT_VOLUME_CLAIM_SPEC_H
#define _NAVAGRAHA_KUBEENT_PERSISTENT_VOLUME_CLAIM_SPEC_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/typed_local_object_reference.hpp"
#include "kubeent/resource_requirements.hpp"
#include "kubeent/label_selector.hpp"

namespace navagraha {
namespace kubeent {

extern char PERSISTENT_VOLUME_CLAIM_SPEC_ACCESS_MODES[];
extern char PERSISTENT_VOLUME_CLAIM_SPEC_DATA_SOURCE[];
extern char PERSISTENT_VOLUME_CLAIM_SPEC_RESOURCES[];
extern char PERSISTENT_VOLUME_CLAIM_SPEC_SELECTOR[];
extern char PERSISTENT_VOLUME_CLAIM_SPEC_STORAGE_CLASS_NAME[];
extern char PERSISTENT_VOLUME_CLAIM_SPEC_VOLUME_MODE[];
extern char PERSISTENT_VOLUME_CLAIM_SPEC_VOLUME_NAME[];

class persistent_volume_claim_spec : public serializable<persistent_volume_claim_spec> {
public:
    extensions::field<
        extensions::special_list<std::string>,
        PERSISTENT_VOLUME_CLAIM_SPEC_ACCESS_MODES> access_modes;
    extensions::field<
        typed_local_object_reference,
        PERSISTENT_VOLUME_CLAIM_SPEC_DATA_SOURCE> data_source;
    extensions::field<resource_requirements, PERSISTENT_VOLUME_CLAIM_SPEC_RESOURCES> resources;
    extensions::field<label_selector, PERSISTENT_VOLUME_CLAIM_SPEC_SELECTOR> selector;
    extensions::field<std::string, PERSISTENT_VOLUME_CLAIM_SPEC_STORAGE_CLASS_NAME> storage_class_name;
    extensions::field<std::string, PERSISTENT_VOLUME_CLAIM_SPEC_VOLUME_MODE> volume_mode;
    extensions::field<std::string, PERSISTENT_VOLUME_CLAIM_SPEC_VOLUME_NAME> volume_name;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
