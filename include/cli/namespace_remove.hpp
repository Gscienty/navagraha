#ifndef _NAVAGRAHA_CLI_NAMESPACE_REMOVE_H
#define _NAVAGRAHA_CLI_NAMESPACE_REMOVE_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"
#include "http_client/curl_helper.hpp"

namespace navagraha {
namespace cli {

extern char CLI_NAMESPACE_REMOVE[];

class namespace_remove : public cli_arg::abstract_process<namespace_remove> {
private:
    cli_arg::arg<CLI_NAMESPACE_REMOVE, 1> remove_arg;

public:
    virtual void bind(cli_arg::process_helper<namespace_remove> & helper) override;
    virtual bool satisfy() const override;
    virtual int execute() override;

};

}
}
#endif
