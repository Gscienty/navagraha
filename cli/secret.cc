#include "cli/secret.hpp"
#include "cli/secret_add.hpp"
#include "cli/secret_remove.hpp"
#include "cli/secret_list.hpp"
#include "cli_arg/process_collection.hpp"

namespace navagraha {
namespace cli {

char CLI_SECRET_FLAG[] = "secret";

void secret::bind(cli_arg::process_helper<secret> & helper)
{
    helper
        .add(this->name_flag);
}

bool secret::satisfy() const
{
    return this->name_flag.used();
}

int secret::execute()
{
    return navagraha::cli_arg::process_collection(this->name_flag.argc(),
                                                  this->name_flag.argv())
        .add(secret_add())
        .add(secret_remove())
        .add(secret_list())
        .result();
}

}
}
