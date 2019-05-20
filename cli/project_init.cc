#include "cli/project_init.hpp"
#include "git/repo_init.hpp"

namespace navagraha {
namespace cli {

char CLI_PROJECT_INIT_PATH[] = "init";
char CLI_PROJECT_INIT_LANG[] = "--lang";

void project_init::bind(cli_arg::process_helper<project_init> & helper)
{
    this->arg_lang.require(this->arg_path);

    helper
        .add(this->arg_path)
        .add(this->arg_lang);
}

bool project_init::satisfy() const
{
    return this->arg_path.used()
        && this->arg_lang.used();
}

int project_init::execute()
{
    navagraha::git::repo_init git_repo(this->arg_path[0],
                                       "https://github.com/Gscienty/navagraha.git",
                                       "template/" + this->arg_lang[0]);

    git_repo.init();
    git_repo.fetch_template();

    return 0;
}


}
}
