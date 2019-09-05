#include "cli/node.hpp"
#include "cli/config.hpp"
#include "process/node.hpp"
#include <iostream>
#include <sstream>

namespace navagraha {
namespace cli {

char CLI_NODE_FLAG[] = "node";

void node::bind(cli_arg::process_helper<node> & helper)
{
    helper.add(this->name_flag);
}

bool node::satisfy() const
{
    return this->name_flag.used();
}

int node::execute()
{
    std::ostringstream oss;
    process::node(config::get_instance()).list().serialize(oss);

    std::cout << oss.str() << std::endl;

    return 0;
}

}
}
