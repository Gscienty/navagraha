#include "cli/config_map.hpp"
#include "cli_arg/process_collection.hpp"
#include "cli/config_map_add.hpp"

namespace navagraha {
namespace cli {

char CLI_CONFIG_MAP_FLAG[] = "config";

void config_map::bind(cli_arg::process_helper<config_map> & helper)
{
    helper
        .add(this->name_flag);
}

bool config_map::satisfy() const
{
    return this->name_flag.used();
}

int config_map::execute()
{
    return navagraha::cli_arg::process_collection(this->name_flag.argc(),
                                                  this->name_flag.argv())
        .add(config_map_add())
        .result();
}

}
}

