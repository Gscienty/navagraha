#include "cli/project.hpp"
#include "cli/project_init.hpp"
#include "cli/project_build.hpp"
#include "cli_arg/process_collection.hpp"

namespace navagraha {
namespace cli {

char CLI_PROJECT_FLAG[] = "project";

void project::bind(cli_arg::process_helper<project> & helper) {
    helper
        .add(this->name_flag);
}

bool project::satisfy() const {
    return this->name_flag.used();
}

int project::execute() {
    return navagraha::cli_arg::process_collection(this->name_flag.argc(),
                                                  this->name_flag.argv())
        .add(project_init())
        .add(project_build())
        .result();
}
}
}
