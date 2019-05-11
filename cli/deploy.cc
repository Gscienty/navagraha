#include "cli/deploy.hpp"

namespace navagraha {
namespace cli {

char CLI_DEPLOY_NAME[] = "deploy";

void deploy::bind(cli_arg::process_helper<deploy> & helper)
{
    helper
        .add(this->switched_flag);
}

bool deploy::satisfy() const 
{
    if (!this->switched_flag.used()) {
        return false;
    }

    return true;
}

int deploy::execute()
{
    return 0;
}


}
}
