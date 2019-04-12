#ifndef _NAVAGRAHA_KUBEENT_CRON_JOB_H
#define _NAVAGRAHA_KUBEENT_CRON_JOB_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/object_meta.hpp"
#include "kubeent/cron_job_spec.hpp"
#include "kubeent/cron_job_status.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char CRON_JOB_API_VERSION[];
extern char CRON_JOB_KIND[];
extern char CRON_JOB_METADATA[];
extern char CRON_JOB_SPEC[];
extern char CRON_JOB_STATUS[];

class cron_job : public serializable<cron_job> {
public:
    extensions::field<std::string, CRON_JOB_API_VERSION> api_version;
    extensions::field<std::string, CRON_JOB_KIND> kind;
    extensions::field<object_meta, CRON_JOB_METADATA> metadata;
    extensions::field<cron_job_spec, CRON_JOB_SPEC> spec;
    extensions::field<cron_job_status, CRON_JOB_STATUS> status;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
