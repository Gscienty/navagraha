#ifndef _NAVAGAHA_CLI_DEPLOY_H
#define _NAVAGAHA_CLI_DEPLOY_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"
#include "http_client/curl_helper.hpp"

namespace navagraha {
namespace cli {

extern char CLI_DEPLOY_NAME[];
extern char CLI_DEPLOY_POLICY[];
extern char CLI_DEPLOY_IMAGE[];

class deploy : public cli_arg::abstract_process<deploy> {
private:
    cli_arg::arg<CLI_DEPLOY_NAME, 1> name_arg;
    cli_arg::arg<CLI_DEPLOY_POLICY, 1> policy_arg;
    cli_arg::arg<CLI_DEPLOY_IMAGE, 1> image_arg;

    void create_deployment(http_client::curl_helper & helper);

public:
    virtual void bind(cli_arg::process_helper<deploy> & helper) override;
    virtual int execute() override;
    virtual bool satisfy() const override;

};

}
}

#endif
