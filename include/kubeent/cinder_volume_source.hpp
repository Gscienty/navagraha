#ifndef _NAVAGRAHA_KUBEENT_CINDER_VOLUME_SOURCE_H
#define _NAVAGRAHA_KUBEENT_CINDER_VOLUME_SOURCE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/local_object_reference.hpp"
#include "kubeent/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char CINDER_VOLUME_SOURCE_FS_TYPE[];
extern char CINDER_VOLUME_SOURCE_READ_ONLY[];
extern char CINDER_VOLUME_SOURCE_SECRET_REF[];
extern char CINDER_VOLUME_SOURCE_VOLUME_ID[];

class cinder_volume_source : public serializable<cinder_volume_source> {
public:
    extensions::field<std::string, CINDER_VOLUME_SOURCE_FS_TYPE> fs_type;
    extensions::field<bool, CINDER_VOLUME_SOURCE_READ_ONLY> read_only;
    extensions::field<local_object_reference, CINDER_VOLUME_SOURCE_SECRET_REF> secret_ref;
    extensions::field<std::string, CINDER_VOLUME_SOURCE_VOLUME_ID> volume_id;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
