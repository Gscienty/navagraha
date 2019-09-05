#include "cli/monitor.hpp"
#include "cli_arg/process_collection.hpp"
#include "cli/monitor_start.hpp"
#include "cli/monitor_stop.hpp"
#include "cli/monitor_test_start.hpp"

namespace navagraha {
namespace cli {

char CLI_MONITOR_FLAG[] = "monitor";

void monitor::bind(cli_arg::process_helper<monitor> & helper)
{
    helper
        .add(this->name_flag);
}

bool monitor::satisfy() const
{
    return this->name_flag.used();
}

int monitor::execute()
{
    return navagraha::cli_arg::process_collection(this->name_flag.argc(),
                                                  this->name_flag.argv())
        .add(monitor_start())
        .add(monitor_stop())
        .add(monitor_test_start())
        .result();
}

}
}
