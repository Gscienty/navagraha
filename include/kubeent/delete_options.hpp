#ifndef _NAVAGRAHA_KUBEENT_DELETE_OPTIONS_H
#define _NAVAGRAHA_KUBEENT_DELETE_OPTIONS_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/preconditions.hpp"

namespace navagraha {
namespace kubeent {

extern char DELETE_OPTIONS_API_VERSION[];
extern char DELETE_OPTIONS_DRY_RUN[];
extern char DELETE_OPTIONS_GRACE_PERIOD_SECONDS[];
extern char DELETE_OPTIONS_KIND[];
extern char DELETE_OPTIONS_ORPHAN_DEPENDENTS[];
extern char DELETE_OPTIONS_PRECONDITIONS[];
extern char DELETE_OPTIONS_PROPAGATION_POLICY[];

class delete_options : public extensions::serializable<delete_options> {
public:
    extensions::field<std::string, DELETE_OPTIONS_API_VERSION> api_version;
    extensions::field<
        extensions::special_list<std::string>,
        DELETE_OPTIONS_DRY_RUN> dry_run;
    extensions::field<int, DELETE_OPTIONS_GRACE_PERIOD_SECONDS> grace_period_seconds;
    extensions::field<std::string, DELETE_OPTIONS_KIND> kind;
    extensions::field<bool, DELETE_OPTIONS_ORPHAN_DEPENDENTS> orphan_dependents;
    extensions::field<preconditions, DELETE_OPTIONS_PRECONDITIONS> preconditons_;
    extensions::field<std::string, DELETE_OPTIONS_PROPAGATION_POLICY> propagation_policy;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
