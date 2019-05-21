#ifndef _NAVAGRAHA_CLI_NAMESPACE_H
#define _NAVAGRAHA_CLI_NAMESPACE_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/process_arg.hpp"
#include "http_client/curl_helper.hpp"
#include "cli/namespace_list.hpp"

namespace navagraha {
namespace cli {

extern char CLI_NAMESPACE_FLAG[];

class namespace_ : public cli_arg::abstract_process<namespace_> {
private:
    cli_arg::process_arg<CLI_NAMESPACE_FLAG> name_flag;

public:
    virtual void bind(cli_arg::process_helper<namespace_> & helper) override;
    virtual bool satisfy() const override;
    virtual int execute() override;
};

}
}

#endif
