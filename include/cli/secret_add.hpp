#ifndef _NAVAGRAHA_CLI_SECRET_ADD_H
#define _NAVAGRAHA_CLI_SECRET_ADD_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"
#include "cli_arg/multi_arg.hpp"
#include "http_client/curl_helper.hpp"

namespace navagraha {
namespace cli {

extern char CLI_SECRET_ADD[];
extern char CLI_SECRET_ADD_NAMESPACE[];
extern char CLI_SECRET_ADD_VALUE[];
extern char CLI_SECRET_ADD_FILE[];

class secret_add : public cli_arg::abstract_process<secret_add> {
private:
    cli_arg::arg<CLI_SECRET_ADD, 1> add_arg;
    cli_arg::arg<CLI_SECRET_ADD_NAMESPACE, 1> namespace_arg;
    cli_arg::multi_arg<CLI_SECRET_ADD_VALUE, 2> value_arg;
    cli_arg::multi_arg<CLI_SECRET_ADD_FILE, 2> file_arg;

    std::string get_file_content(std::string & filename);

public:
    virtual void bind(cli_arg::process_helper<secret_add> & helper) override;
    virtual bool satisfy() const override;
    virtual int execute() override;
};

}
}

#endif
