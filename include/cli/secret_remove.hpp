#ifndef _NAVAGRAHA_CLI_SECRET_REMOVE_H
#define _NAVAGRAHA_CLI_SECRET_REMOVE_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"
#include "http_client/curl_helper.hpp"

namespace navagraha {
namespace cli {

extern char CLI_SECRET_REMOVE[];
extern char CLI_SECRET_REMOVE_NAMESPACE[];

class secret_remove : public cli_arg::abstract_process<secret_remove> {
private:
    cli_arg::arg<CLI_SECRET_REMOVE, 1> remove_arg;
    cli_arg::arg<CLI_SECRET_REMOVE_NAMESPACE, 1> namespace_arg;

public:
    virtual void bind(cli_arg::process_helper<secret_remove> & helper) override;
    virtual bool satisfy() const override;
    virtual int execute() override;
};

}
}

#endif
