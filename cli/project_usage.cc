#include "cli/project_usage.hpp"
#include <iostream>

namespace navagraha {
namespace cli {


int project_usage::execute() 
{
    std::cout
        << std::endl
        << "Welcome to use Nava project management."  << std::endl << std::endl
        << "You can use Nava project management with the following commands:" << std::endl
        << "  " << "init" << "  " << "Initialize a project" << std::endl
        << "  " << "    " << "  " << "usage:" << "  " << "nava project init {project_path} --lang {project_lang}" << std::endl
        << "  " << "    " << "  " << "  " << "project_path" << "  " << "project path" << std::endl
        << "  " << "    " << "  " << "  " << "project_lang" << "  " << "project language" << std::endl
        << "  " << "    " << "  " << "  " << "lang type:" << std::endl
        << "  " << "    " << "  " << "  " << "  " << "python" << std::endl
        << "  " << "    " << "  " << "  " << "  " << "java" << std::endl
        << "  " << "build" << "  " << "Build a project" << std::endl
        << "  " << "    " << "  " << "usage:" << "  " << "nava project build [--path {project_path}]" << std::endl
        << "  " << "    " << "  " << "  " << "project_path" << "  " << "project path, default \".\"" << std::endl
        << std::endl;
    return 0;
}

}
}
