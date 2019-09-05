#include "cli/monitor_test_start.hpp"
#include "cli/config.hpp"
#include "process/monitor.hpp"

namespace navagraha {
namespace cli {

char CLI_MONITOR_TEST_START_FLAG[] = "test";

void monitor_test_start::bind(cli_arg::process_helper<monitor_test_start> & helper)
{
    helper.add(this->init_flag);
}

bool monitor_test_start::satisfy() const
{
    return this->init_flag.used();
}

int monitor_test_start::execute()
{
    process::monitor(config::get_instance()).start(this->init_flag[0]);

    return 0;
}

}
}
