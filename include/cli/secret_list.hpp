#ifndef _NAVAGRAHA_CLI_SECRET_LIST_H
#define _NAVAGRAHA_CLI_SECRET_LIST_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"
#include "http_client/curl_helper.hpp"
#include "kubeent/secret.hpp"

namespace navagraha {
namespace cli {

extern char CLI_SECRET_LIST[];
extern char CLI_SECRET_LIST_NAMESPACE[];

class secret_list : public cli_arg::abstract_process<secret_list> {
private:
    cli_arg::arg<CLI_SECRET_LIST, 0> list_arg;
    cli_arg::arg<CLI_SECRET_LIST_NAMESPACE, 1> namespace_arg;

    void display_secret(kubeent::secret & sec);

public:
    virtual void bind(cli_arg::process_helper<secret_list> & helper) override;
    virtual bool satisfy() const override;
    virtual int execute() override;

};

}
}

#endif
