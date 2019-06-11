#include "cli/monitor_break.hpp"

namespace navagraha {
namespace cli {

void monitor_break::bind(cli_arg::process_helper<monitor_break> & helper)
{
    helper
        .add(this->break_flag);
}

bool monitor_break::satisfy() const
{
    return this->break_flag.used();
}

int monitor_break::execute()
{

    return 0;
}

}
}
