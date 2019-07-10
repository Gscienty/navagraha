#include "cli/cli_usage.hpp"
#include <iostream>

namespace navagraha {
namespace cli {


int cli_usage::execute()
{
    std::cout
        << std::endl
        << "Welcome to use Nava! Make FaaS Simple."  << std::endl << std::endl
        << "You can use Nava with the following commands:" << std::endl
        << "  " << "func" << "\t\t" << "provides functions such as upline, offline and update of function service." << std::endl
        << "  " << "project" << "\t" << "the construction of a function service project." << std::endl
        << "  " << "namespace" << "\t" << "management of funtion service namespaces." << std::endl
        << "  " << "secret" << "\t" << "managing secret in function service." << std::endl
        << "  " << "monitor" << "\t" << "service monitoring." << std::endl
        << "  " << "gateway" << "\t" << "function service gateway management." << std::endl
        << "  " << "config" << "\t" << "managing config in function service." << std::endl << std::endl
        << "Usage:" << std::endl
        << "  " << "nava <command> [options]" << std::endl << std::endl
        << "Use \"nava <command> --help\" for more information about a given command." << std::endl
        << std::endl;


    return 0;
}

}
}
