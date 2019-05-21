#ifndef _NAVAGRAHA_CLI_NAMESPACE_ADD_H
#define _NAVAGRAHA_CLI_NAMESPACE_ADD_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"
#include "http_client/curl_helper.hpp"

namespace navagraha {
namespace cli {

extern char CLI_NAMESPACE_ADD[];

class namespace_add : public cli_arg::abstract_process<namespace_add> {
private:
    cli_arg::arg<CLI_NAMESPACE_ADD, 1> add_arg;

public:
    virtual void bind(cli_arg::process_helper<namespace_add> & helper) override;
    virtual bool satisfy() const override;
    virtual int execute() override;
};

}
}

#endif
