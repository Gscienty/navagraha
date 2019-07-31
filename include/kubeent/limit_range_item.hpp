#ifndef _NAVAGRAHA_KUBEENT_LIMIT_RANGE_ITEM_H
#define _NAVAGRAHA_KUBEENT_LIMIT_RANGE_ITEM_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "extensions/common_object.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char LIMIT_RANGE_ITEM_DEFAULT[];
extern char LIMIT_RANGE_ITEM_DEFAULT_REQUEST[];
extern char LIMIT_RANGE_ITEM_MAX[];
extern char LIMIT_RANGE_ITEM_MAX_LIMIT_REQUEST_RATIO[];
extern char LIMIT_RANGE_ITEM_MIN[];
extern char LIMIT_RANGE_ITEM_TYPE[];

class limit_range_item : public extensions::serializable<limit_range_item> {
public:
    extensions::field<extensions::common_object, LIMIT_RANGE_ITEM_DEFAULT> default_;
    extensions::field<extensions::common_object, LIMIT_RANGE_ITEM_DEFAULT_REQUEST> default_request;
    extensions::field<extensions::common_object, LIMIT_RANGE_ITEM_MAX> max;
    extensions::field<extensions::common_object, LIMIT_RANGE_ITEM_MAX_LIMIT_REQUEST_RATIO> max_limit_request_ratio;
    extensions::field<extensions::common_object, LIMIT_RANGE_ITEM_MIN> min;
    extensions::field<std::string, LIMIT_RANGE_ITEM_TYPE> type;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
