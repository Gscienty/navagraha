#ifndef _NAVAGRAHA_CLI_SECRET_H
#define _NAVAGRAHA_CLI_SECRET_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/process_arg.hpp"
#include "http_client/curl_helper.hpp"

namespace navagraha {
namespace cli {

extern char CLI_SECRET_FLAG[];

class secret : public cli_arg::abstract_process<secret> {
private:
    cli_arg::process_arg<CLI_SECRET_FLAG> name_flag;

public:
    virtual void bind(cli_arg::process_helper<secret> & helper) override;
    virtual bool satisfy() const override;
    virtual int execute() override;
};

}
}

#endif
