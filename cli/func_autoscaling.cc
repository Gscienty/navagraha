#include "cli/func_autoscaling.hpp"
#include "cli/config.hpp"
#include "kubeent/horizontal_pod_autoscaler.hpp"
#include "kube_api/horizontal_pod_autoscaler.hpp"
#include "process/func.hpp"

namespace navagraha {
namespace cli {

char CLI_FUNC_AUTOSCALING_FLAG[] = "autoscaling";
char CLI_FUNC_AUTOSCALING_NAME[] = "--name";
char CLI_FUNC_AUTOSCALING_LIST[] = "--list";
char CLI_FUNC_AUTOSCALING_NAMESPACE[] = "--namespace";
char CLI_FUNC_AUTOSCALING_CPU[] = "--cpu";
char CLI_FUNC_AUTOSCALING_MIN[] = "--min";
char CLI_FUNC_AUTOSCALING_MAX[] = "--max";

void func_autoscaling::bind(cli_arg::process_helper<func_autoscaling> & helper)
{
    this->cpu_arg.require(this->flag_arg);
    this->name_arg.require(this->flag_arg);
    this->namespace_arg.require(this->flag_arg);
    this->min_arg.require(this->flag_arg);
    this->max_arg.require(this->flag_arg);
    this->list_arg.require(this->flag_arg);

    helper
        .add(this->flag_arg)
        .add(this->name_arg)
        .add(this->namespace_arg)
        .add(this->list_arg)
        .add(this->cpu_arg)
        .add(this->min_arg)
        .add(this->max_arg);
}

bool func_autoscaling::satisfy() const
{
    return this->flag_arg.used();
}

int func_autoscaling::execute()
{
    if (this->list_arg.used()) {
        return this->list();
    }
    else {
        return this->add();
    }
}

int func_autoscaling::list()
{
    process::func_autoscaling_list_arg arg;
    arg.namespace_ = this->namespace_arg[0];
    auto ret = process::func(config::get_instance()).list_autoscaling(arg).values();

    for (auto & item : ret) {
        std::cout
            << item.name.get()
            << '\t'
            << item.cpu
            << '\t'
            << item.max
            << '-'
            << item.min
            << '\n';
    }

    return 0;
}

int func_autoscaling::add()
{
    std::string namespace_ = "default";
    http_client::curl_helper helper(config::get_instance().kube_cert,
                                    config::get_instance().kube_key,
                                    config::get_instance().kube_ca,
                                    config::get_instance().kube_api_server);
    if (this->namespace_arg.used()) {
        namespace_ = this->namespace_arg[0];
    }

    kubeent::horizontal_pod_autoscaler hpa;
    hpa.api_version = "autoscaling/v1";
    hpa.kind = "HorizontalPodAutoscaler";
    hpa.metadata.get().name = std::string(this->name_arg[0]);
    hpa.spec.get().cpu_utilization_percentage = ::atoi(this->cpu_arg[0].c_str());
    hpa.spec.get().min_replicas = ::atoi(this->min_arg[0].c_str());
    hpa.spec.get().max_replicas = ::atoi(this->max_arg[0].c_str());
    hpa.spec.get().scale_target_ref.get().api_version = std::string("apps/v1");
    hpa.spec.get().scale_target_ref.get().kind = std::string("Deployment");
    hpa.spec.get().scale_target_ref.get().name = std::string(this->name_arg[0]);

    helper.build<kube_api::horizontal_pod_autoscaler>()
        .create(namespace_, hpa)
        .response_switch()
        .response_case<200, kubeent::horizontal_pod_autoscaler>([] (kubeent::horizontal_pod_autoscaler &) -> void {
                                                                std::cout << "autoscaling create." << std::endl;
                                                                })
        .response_case<201, kubeent::horizontal_pod_autoscaler>([] (kubeent::horizontal_pod_autoscaler &) -> void {
                                                                std::cout << "autoscaling created." << std::endl;
                                                                })
        .response_case<202, kubeent::horizontal_pod_autoscaler>([] (kubeent::horizontal_pod_autoscaler &) -> void {
                                                                std::cout << "autoscaling create accepted." << std::endl;
                                                                });
    return 0;
}

}
}
