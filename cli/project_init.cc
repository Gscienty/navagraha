#include "cli/project_init.hpp"
#include "git/repo_init.hpp"
#include "process/project.hpp"

namespace navagraha {
namespace cli {

char CLI_PROJECT_INIT_PATH[] = "init";
char CLI_PROJECT_INIT_LANG[] = "--lang";
char CLI_PROJECT_INIT_LOCAL[] = "--local";

void project_init::bind(cli_arg::process_helper<project_init> & helper)
{
    this->arg_lang.require(this->arg_path);
    this->arg_local.require(this->arg_path);

    helper
        .add(this->arg_path)
        .add(this->arg_lang)
        .add(this->arg_local);
}

bool project_init::satisfy() const
{
    return this->arg_path.used()
        && this->arg_lang.used();
}

int project_init::execute()
{
    process::project_init_arg arg;

    arg.use_local = this->arg_local.used();
    if (arg.use_local) {
        arg.local_template_path = this->arg_local[0];
    }
    arg.path = this->arg_path[0];
    arg.type = this->arg_lang[0];

    process::project(config::get_instance()).init(arg);

    return 0;
}


}
}
