#ifndef _NAVAGRAHA_KUBEENT_ENDPOINT_SUBSET_H
#define _NAVAGRAHA_KUBEENT_ENDPOINT_SUBSET_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/endpoint_address.hpp"
#include "kubeent/endpoint_port.hpp"

namespace navagraha {
namespace kubeent {

extern char ENDPOINT_SUBSET_ADDRESSES[];
extern char ENDPOINT_SUBSET_NOT_READY_ADDRESSES[];
extern char ENDPOINT_SUBSET_PORTS[];

class endpoint_subset : public serializable<endpoint_subset> {
public:
    extensions::field<
        extensions::special_list<endpoint_address>,
        ENDPOINT_SUBSET_ADDRESSES> addresses;
    extensions::field<
        extensions::special_list<endpoint_address>,
        ENDPOINT_SUBSET_NOT_READY_ADDRESSES> not_ready_addresses;
    extensions::field<
        extensions::special_list<endpoint_port>,
        ENDPOINT_SUBSET_PORTS> ports;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
