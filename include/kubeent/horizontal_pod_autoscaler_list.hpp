#ifndef _NAVAGRAHA_KUBEENTT_HORIZONTAL_POD_AUTOSCALER_LIST_H
#define _NAVAGRAHA_KUBEENTT_HORIZONTAL_POD_AUTOSCALER_LIST_H

#include "extensions/serializable.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/field.hpp"
#include "extensions/special_list.hpp"
#include "kubeent/list_meta.hpp"
#include "kubeent/horizontal_pod_autoscaler.hpp"

namespace navagraha {
namespace kubeent {

extern char HORIZONTAL_POD_AUTOSCALER_LIST_API_VERSION[];
extern char HORIZONTAL_POD_AUTOSCALER_LIST_ITEMS[];
extern char HORIZONTAL_POD_AUTOSCALER_LIST_KIND[];
extern char HORIZONTAL_POD_AUTOSCALER_LIST_METADATA[];

class horizontal_pod_autoscaler_list : public extensions::serializable<horizontal_pod_autoscaler_list> {
public:
    extensions::field<std::string, HORIZONTAL_POD_AUTOSCALER_LIST_API_VERSION> api_version;
    extensions::field<std::string, HORIZONTAL_POD_AUTOSCALER_LIST_KIND> kind;
    extensions::field<extensions::special_list<horizontal_pod_autoscaler>, HORIZONTAL_POD_AUTOSCALER_LIST_ITEMS> items;
    extensions::field<list_meta, HORIZONTAL_POD_AUTOSCALER_METADATA> metadata;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
