#include "cli/namespace.hpp"
#include "cli/namespace_list.hpp"
#include "cli_arg/process_collection.hpp"

namespace navagraha {
namespace cli {

char CLI_NAMESPACE_FLAG[] = "namespace";

void namespace_::bind(cli_arg::process_helper<namespace_> & helper)
{
    helper
        .add(this->name_flag);
}

bool namespace_::satisfy() const
{
    return this->name_flag.used();
}

int namespace_::execute()
{
    return navagraha::cli_arg::process_collection(this->name_flag.argc(),
                                                  this->name_flag.argv())
        .add(navagraha::cli::namespace_list())
        .result();
}

}
}
