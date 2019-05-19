#include "cli/func_add.hpp"
#include "cli/func_del.hpp"
#include "cli/image_build.hpp"
#include "cli_arg/process_collection.hpp"

int main(int argc, char ** argv)
{
    return navagraha::cli_arg::process_collection(argc, argv)
        .add(navagraha::cli::func_add())
        .add(navagraha::cli::func_del())
        .add(navagraha::cli::image_build())
        .result();
}
