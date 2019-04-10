#ifndef _NAVAGRAHA_KUBEENT_QUOBYTE_VOLUME_SOURCE_H
#define _NAVAGRAHA_KUBEENT_QUOBYTE_VOLUME_SOURCE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char QUOBYTE_VOLUME_SOURCE_GROUP[];
extern char QUOBYTE_VOLUME_SOURCE_READ_ONLY[];
extern char QUOBYTE_VOLUME_SOURCE_REGISTRY[];
extern char QUOBYTE_VOLUME_SOURCE_USER[];
extern char QUOBYTE_VOLUME_SOURCE_VOLUME[];

class quobyte_volume_source : public serializable<quobyte_volume_source> {
public:
    extensions::field<
        std::string,
        QUOBYTE_VOLUME_SOURCE_GROUP> group;
    extensions::field<
        bool,
        QUOBYTE_VOLUME_SOURCE_READ_ONLY> read_only;
    extensions::field<
        std::string,
        QUOBYTE_VOLUME_SOURCE_REGISTRY> registry;
    extensions::field<
        std::string,
        QUOBYTE_VOLUME_SOURCE_USER> user;
    extensions::field<
        std::string,
        QUOBYTE_VOLUME_SOURCE_VOLUME> volume;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
