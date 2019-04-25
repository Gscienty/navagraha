#include "kube_api/job.hpp"

namespace navagraha {
namespace kube_api {

kubeent::job job::create(const std::string namespace_,
                         kubeent::job & job_)
{
    this->set_payload(job_);
    return this->post_call<kubeent::job>("/apis/batch/v1/namespaces/"
                                         + namespace_
                                         + "/jobs");
}
kubeent::job job::replace(const std::string namespace_,
                          const std::string name,
                          kubeent::job & job_)
{
    this->set_payload(job_);
    return this->put_call<kubeent::job>("/apis/batch/v1/namespaces/"
                                        + namespace_
                                        + "/jobs/"
                                        + name);
}
kubeent::status job::delete_(const std::string namespace_,
                             const std::string name,
                             kubeent::delete_options & obt)
{
    this->set_payload(obt);
    return this->delete_call<kubeent::status>("/apis/batch/v1/namespaces/"
                                              + namespace_
                                              + "/jobs/"
                                              + name);
}

kubeent::status job::delete_collection(const std::string namespace_)
{
    return this->delete_call<kubeent::status>("/apis/batch/v1/namespaces/"
                                              + namespace_
                                              + "/jobs");
}

kubeent::job job::read(const std::string namespace_,
                       const std::string name)
{
    return this->get_call<kubeent::job>("/apis/batch/v1/namespaces/"
                                        + namespace_
                                        + "/jobs/"
                                        + name);
}

kubeent::job_list job::list(const std::string namespace_)
{
    return this->get_call<kubeent::job_list>("/apis/batch/v1/namespaces/"
                                             + namespace_
                                             + "/jobs");
}

kubeent::job_list job::list_all_namespace()
{
    return this->get_call<kubeent::job_list>("/apis/batch/v1/jobs");
}

}
}
