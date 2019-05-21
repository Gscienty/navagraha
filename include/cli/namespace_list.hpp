#ifndef _NAVAGRAHA_CLI_NAMESPACE_LIST_H
#define _NAVAGRAHA_CLI_NAMESPACE_LIST_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"
#include "http_client/curl_helper.hpp"
#include "kubeent/namespace.hpp"

namespace navagraha {
namespace cli {

extern char CLI_NAMESPACE_LIST_FLAG[];

class namespace_list : public cli_arg::abstract_process<namespace_list> {
private:
    cli_arg::arg<CLI_NAMESPACE_LIST_FLAG, 0> list_flag;

    void display_item(kubeent::namespace_ & namespace_);
public:
    virtual void bind(cli_arg::process_helper<namespace_list> & helper) override;
    virtual bool satisfy() const override;
    virtual int execute() override;

};

}
}

#endif
