#include "cli/monitor_test_start.hpp"
#include "cli/config.hpp"
#include "process/monitor.hpp"
#include <sstream>
#include <iostream>

namespace navagraha {
namespace cli {

char CLI_MONITOR_TEST_START_FLAG[] = "test";
char CLI_MONITOR_TEST_START_EXIST[] = "--exist";
char CLI_MONITOR_TEST_START_REMOVE[] = "--remove";

void monitor_test_start::bind(cli_arg::process_helper<monitor_test_start> & helper)
{
    this->exist_flag.require(this->init_flag);
    this->remove_flag.require(this->init_flag);
    helper
        .add(this->init_flag)
        .add(this->exist_flag)
        .add(this->remove_flag);
}

bool monitor_test_start::satisfy() const
{
    return this->init_flag.used();
}

int monitor_test_start::execute()
{
    if (this->exist_flag.used()) {
        std::ostringstream oss;
        process::monitor(config::get_instance()).get(this->init_flag[0]).serialize(oss);
        std::cout << oss.str() << std::endl;
    }
    else if (this->remove_flag.used()) {
        process::monitor(config::get_instance()).remove(this->init_flag[0]);
    }
    else {
        process::monitor(config::get_instance()).start(this->init_flag[0]);
    }

    return 0;
}

}
}
