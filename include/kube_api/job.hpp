#ifndef _NAVAGRAHA_KUBE_API_JOB_H
#define _NAVAGRAHA_KUBE_API_JOB_H

#include "http_client/client.hpp"
#include "kubeent/job.hpp"
#include "kubeent/job_list.hpp"
#include "kubeent/delete_options.hpp"
#include "kubeent/status.hpp"

namespace navagraha {
namespace kube_api {

class job : public http_client::client {
public:
    job(CURL * curl, std::string host);

    kubeent::job create(const std::string namespace_,
                        kubeent::job & job_);

    kubeent::job replace(const std::string namespace_,
                         const std::string name,
                         kubeent::job & job_);

    kubeent::status delete_(const std::string namespace_,
                            const std::string name,
                            kubeent::delete_options & obt);

    kubeent::status delete_collection(const std::string namespace_);

    kubeent::job read(const std::string namespace_,
                      const std::string name);

    kubeent::job_list list(const std::string namespace_);

    kubeent::job_list list_all_namespace();
};

}
}

#endif
