#include "cli/gateway.hpp"
#include "cli/gateway_init.hpp"
#include "cli_arg/process_collection.hpp"

namespace navagraha {
namespace cli {

char CLI_GATEWAY_FLAG[] = "gateway";

void gateway::bind(cli_arg::process_helper<gateway> & helper)
{
    helper.add(this->name_flag);
}

bool gateway::satisfy() const
{
    return this->name_flag.used();
}

int gateway::execute()
{
    return navagraha::cli_arg::process_collection(this->name_flag.argc(),
                                                  this->name_flag.argv())
        .add(gateway_init())
        .result();
}

}
}
