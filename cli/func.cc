#include "cli/func.hpp"
#include "cli/func_up.hpp"
#include "cli/func_down.hpp"
#include "cli_arg/process_collection.hpp"

namespace navagraha {
namespace cli {

char CLI_FUNC_FLAG[] = "func";

void func::bind(cli_arg::process_helper<func> & helper)
{
    helper
        .add(this->name_flag);
}

bool func::satisfy() const
{
    return this->name_flag.used();
}

int func::execute()
{

    return navagraha::cli_arg::process_collection(this->name_flag.argc(),
                                                  this->name_flag.argv())
        .add(func_up())
        .add(func_down())
        .result();
}

}
}
