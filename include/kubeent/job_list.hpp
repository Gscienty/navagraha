#ifndef _NAVAGRAHA_KUBEENT_JOB_LIST_H
#define _NAVAGRAHA_KUBEENT_JOB_LIST_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "kubeent/job.hpp"
#include "kubeent/list_meta.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char JOB_LIST_API_VERSION[];
extern char JOB_LIST_ITEMS[];
extern char JOB_LIST_KIND[];
extern char JOB_LIST_METADATA[];

class job_list : public serializable<job_list> {
public:
    extensions::field<std::string, JOB_LIST_API_VERSION> api_version;
    extensions::field<
        extensions::special_list<job>, JOB_LIST_ITEMS> items;
    extensions::field<std::string, JOB_LIST_KIND> kind;
    extensions::field<list_meta, JOB_LIST_METADATA> metadata;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
