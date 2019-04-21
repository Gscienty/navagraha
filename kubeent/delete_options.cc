#include "kubeent/delete_options.hpp"

namespace navagraha {
namespace kubeent {
char DELETE_OPTIONS_API_VERSION[] = "apiVersion";
char DELETE_OPTIONS_DRY_RUN[] = "dryRun";
char DELETE_OPTIONS_GRACE_PERIOD_SECONDS[] = "gracePeriodSeconds";
char DELETE_OPTIONS_KIND[] = "kind";
char DELETE_OPTIONS_ORPHAN_DEPENDENTS[] = "orphanDependents";
char DELETE_OPTIONS_PRECONDITIONS[] = "preconditions";
char DELETE_OPTIONS_PROPAGATION_POLICY[] = "propagationPolicy";

void delete_options::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->dry_run)
        .add(this->grace_period_seconds)
        .add(this->kind)
        .add(this->orphan_dependents)
        .add(this->preconditons_)
        .add(this->propagation_policy);
}

}
}
