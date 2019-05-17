#ifndef _NAVAGRAHA_CLI_image_build_H
#define _NAVAGRAHA_CLI_image_build_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"
#include "http_client/curl_helper.hpp"

namespace navagraha {
namespace cli {

extern char IMAGE_BUILD[];
extern char IMAGE_TAG[];
extern char IMAGE_PATH[];

class image_build : public cli_arg::abstract_process<image_build> {
private:
    cli_arg::arg<IMAGE_BUILD, 1> build_arg;
    cli_arg::arg<IMAGE_PATH, 1> path_arg;

    void received_callback(std::string & msg);

public:
    virtual void bind(cli_arg::process_helper<image_build> & helper) override;
    virtual int execute() override;
    virtual bool satisfy() const override;
};

}
}

#endif
