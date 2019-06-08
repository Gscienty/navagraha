#ifndef _NAVAGRAHA_KUBEENT_VOLUME_H
#define _NAVAGRAHA_KUBEENT_VOLUME_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/ceph_fs_volume_source.hpp"
#include "kubeent/cinder_volume_source.hpp"
#include "kubeent/config_map_volume_source.hpp"
#include "kubeent/downward_api_volume_source.hpp"
#include "kubeent/empty_dir_volume_source.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char VOLUME_CEPHFS[];
extern char VOLUME_CINDER[];
extern char VOLUME_CONFIG_MAP[];
extern char VOLUME_DOWNWARD_API[];
extern char VOLUME_EMPTY_DIR[];
extern char VOLUME_NAME[];

class volume : public extensions::serializable<volume> {
public:
    extensions::field<ceph_fs_volume_source, VOLUME_CEPHFS> cephfs;
    extensions::field<cinder_volume_source, VOLUME_CINDER> cinder;
    extensions::field<config_map_volume_source, VOLUME_CONFIG_MAP> config_map;
    extensions::field<downward_api_volume_source, VOLUME_DOWNWARD_API> downward_api;
    extensions::field<empty_dir_volume_source, VOLUME_EMPTY_DIR> empty_dir;
    extensions::field<std::string, VOLUME_NAME> name;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
