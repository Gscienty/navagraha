#include "kube_api/job.hpp"

namespace navagraha {
namespace kube_api {

kubeent::job job::create(const std::string namespace_,
                         kubeent::job & job_)
{
    this->set_payload(job_);
    return this->post_request("/apis/batch/v1/namespaces/"
                              + namespace_
                              + "/jobs")
        .get<kubeent::job>();
}
kubeent::job job::replace(const std::string namespace_,
                          const std::string name,
                          kubeent::job & job_)
{
    this->set_payload(job_);
    return this->put_request("/apis/batch/v1/namespaces/"
                             + namespace_
                             + "/jobs/"
                             + name)
        .get<kubeent::job>();
}
kubeent::status job::delete_(const std::string namespace_,
                             const std::string name,
                             kubeent::delete_options & obt)
{
    this->set_payload(obt);
    return this->delete_request("/apis/batch/v1/namespaces/"
                         + namespace_
                         + "/jobs/"
                         + name)
        .get<kubeent::status>();
}

kubeent::status job::delete_collection(const std::string namespace_)
{
    return this->delete_request("/apis/batch/v1/namespaces/"
                                + namespace_
                                + "/jobs")
        .get<kubeent::status>();
}

kubeent::job job::read(const std::string namespace_,
                       const std::string name)
{
    return this->get_request("/apis/batch/v1/namespaces/"
                             + namespace_
                             + "/jobs/"
                             + name)
        .get<kubeent::job>();
}

kubeent::job_list job::list(const std::string namespace_)
{
    return this->get_request("/apis/batch/v1/namespaces/"
                             + namespace_
                             + "/jobs")
        .get<kubeent::job_list>();
}

kubeent::job_list job::list_all_namespace()
{
    return this->get_request("/apis/batch/v1/jobs")
        .get<kubeent::job_list>();
}

}
}
