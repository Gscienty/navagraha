#include "cli/func_build.hpp"
#include "cli/func_deploy.hpp"
#include "cli/func_offline.hpp"
#include "cli/project_init.hpp"
#include "cli_arg/process_collection.hpp"

int main(int argc, char ** argv)
{
    return navagraha::cli_arg::process_collection(argc, argv)
        .add(navagraha::cli::func_build())
        .add(navagraha::cli::func_deploy())
        .add(navagraha::cli::func_offline())
        .add(navagraha::cli::project_init())
        .result();
}
