#ifndef _NAVAGRAHA_CLI_FUNC_REPO_H
#define _NAVAGRAHA_CLI_FUNC_REPO_H

#include "cli_arg/abstract_process.hpp"
#include "cli_arg/arg.hpp"
#include "cli_arg/process_helper.hpp"
#include "dockerent/image.hpp"
#include "extensions/special_list.hpp"

namespace navagraha {
namespace cli {

extern char CLI_FUNC_REPO_NAME[];

class func_repo : public cli_arg::abstract_process<func_repo> {
private:
    cli_arg::arg<CLI_FUNC_REPO_NAME, 0> name_arg;

    void images_for_each(extensions::special_list<dockerent::image> & images);

    void image_eachor(dockerent::image & image);
public:
    virtual void bind(cli_arg::process_helper<func_repo> & helper) override;
    virtual bool satisfy() const override;
    virtual int execute() override;
};

}
}

#endif
