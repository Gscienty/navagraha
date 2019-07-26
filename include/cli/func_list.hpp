#ifndef _NAVAGRAHA_CLI_FUNC_LIST_H
#define _NAVAGRAHA_CLI_FUNC_LIST_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"
#include "cli_arg/process_helper.hpp"
#include "kubeent/service.hpp"
#include "kubeent/deployment.hpp"
#include <map>
#include <string>

namespace navagraha {
namespace cli {

extern char CLI_FUNC_LIST_NAME[];
extern char CLI_FUNC_LIST_NAMESPACE[];

class func_list : public cli_arg::abstract_process<func_list> {
private:
    cli_arg::arg<CLI_FUNC_LIST_NAME, 0> name_arg;
    cli_arg::arg<CLI_FUNC_LIST_NAMESPACE, 1> namespace_arg;

    void func_service_eachor(std::map<std::string, kubeent::service> & svc_map, kubeent::service & svc);
    void func_deployment_eachor(std::map<std::string, kubeent::service> & svc_map, kubeent::deployment & dep);
public:
    virtual void bind(cli_arg::process_helper<func_list> & helper) override;
    virtual bool satisfy() const override;
    virtual int execute() override;
};

}
}

#endif
