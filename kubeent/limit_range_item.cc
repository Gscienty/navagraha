#include "kubeent/limit_range_item.hpp"

namespace navagraha {
namespace kubeent {

char LIMIT_RANGE_ITEM_DEFAULT[] = "default";
char LIMIT_RANGE_ITEM_DEFAULT_REQUEST[] = "defaultRequest";
char LIMIT_RANGE_ITEM_MAX[] = "max";
char LIMIT_RANGE_ITEM_MAX_LIMIT_REQUEST_RATIO[] = "maxLimitRequestRatio";
char LIMIT_RANGE_ITEM_MIN[] = "min";
char LIMIT_RANGE_ITEM_TYPE[] = "type";

void limit_range_item::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->default_)
        .add(this->default_request)
        .add(this->max)
        .add(this->max_limit_request_ratio)
        .add(this->min)
        .add(this->type);
}

}
}
