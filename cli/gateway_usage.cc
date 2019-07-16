#include "cli/gateway_usage.hpp"
#include <iostream>

namespace navagraha {
namespace cli {

int gateway_usage::execute()
{
    std::cout
        << std::endl
        << "Welcome to use Nava func management."  << std::endl << std::endl
        << "You can use Nava func management with the following commands:" << std::endl
        << "  " << "init" << "   " << "init nava API gateway." << std::endl
        << "  " << "  " << "   " << "usage:" << "  " << "nava gateway init [--policy {policy_name}] [--namespace {namespace}]"  << std::endl
        << "  " << "  " << "   " << "  " << "policy_name" << " " << "node pull docker image policy, values: \"Always\"(default), \"IfNotPresent\", \"Never\"" << std::endl
        << "  " << "  " << "   " << "  " << "namespace" << "   " << "namespaces where API gateway" << std::endl
        << "  " << "list" << "   " << "get nava API gateway." << std::endl
        << "  " << "  " << "   " << "usage:" << "  " << "nava gateway list [--namespace {namespace}]"  << std::endl
        << "  " << "  " << "   " << "  " << "namespace" << "   " << "namespaces where API gateway" << std::endl
        << std::endl;
    return 0;
}

}
}
