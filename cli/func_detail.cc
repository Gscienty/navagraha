#include "cli/func_detail.hpp"
#include "process/func.hpp"
#include "cli/config.hpp"
#include <sstream>
#include <iostream>

namespace navagraha {
namespace cli {

char CLI_FUNC_DETAIL_NAME[] = "detail";
char CLI_FUNC_DETAIL_NAMESPACE[] = "--namespace";
char CLI_FUNC_DETAIL_STATEFUL[] = "--stateful";


void func_detail::bind(cli_arg::process_helper<func_detail> & helper)
{
    this->namespace_arg.require(this->name_arg);
    this->stateful_arg.require(this->name_arg);

    helper
        .add(this->name_arg)
        .add(this->namespace_arg)
        .add(this->stateful_arg);
}

int func_detail::execute()
{
    process::func_detail_arg arg;
    arg.name = this->name_arg[0];
    arg.namespace_ = "default";
    if (this->namespace_arg.used()) {
        arg.namespace_ = this->namespace_arg[0];
    }
    arg.stateful = this->stateful_arg.used();

    std::ostringstream oss;
    process::func(config::get_instance()).detail(arg).serialize(oss);

    std::cout << oss.str() << std::endl;

    return 0;
}

bool func_detail::satisfy() const
{
    return this->name_arg.used();
}

}
}
