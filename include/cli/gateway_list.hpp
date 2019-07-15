#ifndef _NAVAGRAHA_CLI_GATEWAY_LIST_H
#define _NAVAGRAHA_CLI_GATEWAY_LIST_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"
#include "kubeent/pod_list.hpp"

namespace navagraha {
namespace cli {

extern char CLI_GATEWAY_LIST_FLAG[];
extern char CLI_GATEWAY_LIST_NAMESPACE[];

class gateway_list : public cli_arg::abstract_process<gateway_list> {
private:
    cli_arg::arg<CLI_GATEWAY_LIST_FLAG, 0> list_flag;
    cli_arg::arg<CLI_GATEWAY_LIST_NAMESPACE, 1> namespace_arg;

    void gateway_pods_foreach(kubeent::pod_list & pods);
public:
    virtual void bind(cli_arg::process_helper<gateway_list> & helper) override;
    virtual bool satisfy() const override;
    virtual int execute() override;
};

}
}

#endif
