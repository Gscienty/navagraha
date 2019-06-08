#ifndef _NAVAGRAHA_CLI_func_deploy_H
#define _NAVAGRAHA_CLI_func_deploy_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"
#include "http_client/curl_helper.hpp"

namespace navagraha {
namespace cli {

extern char CLI_FUNC_DEPLOY_NAME[];
extern char CLI_FUNC_DEPLOY_POLICY[];
extern char CLI_FUNC_DEPLOY_IMAGE[];
extern char CLI_FUNC_DEPLOY_NAMESPACE[];

class func_up : public cli_arg::abstract_process<func_up> {
private:
    cli_arg::arg<CLI_FUNC_DEPLOY_NAME, 1> name_arg;
    cli_arg::arg<CLI_FUNC_DEPLOY_POLICY, 1> policy_arg;
    cli_arg::arg<CLI_FUNC_DEPLOY_IMAGE, 1> image_arg;
    cli_arg::arg<CLI_FUNC_DEPLOY_NAMESPACE, 1> namespace_arg;

    void create_deployment(std::string namespace_, http_client::curl_helper & helper);
    void create_service(std::string namespace_, http_client::curl_helper & helper);

public:
    virtual void bind(cli_arg::process_helper<func_up> & helper) override;
    virtual int execute() override;
    virtual bool satisfy() const override;

};

}
}

#endif
