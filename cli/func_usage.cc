#include "cli/func_usage.hpp"
#include <iostream>

namespace navagraha {
namespace cli {

int func_usage::execute()
{
    std::cout
        << std::endl
        << "Welcome to use Nava func management."  << std::endl << std::endl
        << "You can use Nava func management with the following commands:" << std::endl
        << "  " << "up" << "   " << "Go online with the specified function service." << std::endl
        << "  " << "  " << "   " << "usage:" << "  " << "nava func up {func_name} --image {image_name} [--policy {policy_name}] [--namespace {namespace}]"  << std::endl
        << "  " << "  " << "   " << "  " << "func_name" << "   " << "function service name in function computing cluster." << std::endl
        << "  " << "  " << "   " << "  " << "image_name" << "  " << "docker image name corresponding to function service." << std::endl
        << "  " << "  " << "   " << "  " << "policy_name" << " " << "node pull docker image policy, values: \"Always\"(default), \"IfNotPresent\", \"Never\"" << std::endl
        << "  " << "  " << "   " << "  " << "namespace" << "   " << "namespaces where function services reside" << std::endl
        << std::endl
        << "  " << "down" << " " << "Logoff the specified function service." << std::endl
        << "  " << "    " << " " << "usage:" << "  " <<  "nava func down {func_name} [--namespace {namespace}]" << std::endl
        << "  " << "    " << " " << "  " << "func_name" << "   " << "function service name in function computing cluster." << std::endl
        << "  " << "    " << " " << "  " << "namespace" << "   " << "namespaces where function services reside" << std::endl
        << std::endl
        << "  " << "repo" << " " << "Enumerate all function services." << std::endl
        << "  " << "    " << " " << "usage:" << "  " <<  "nava func repo [--name {func name}]" << std::endl
        << "  " << "    " << " " << "  " << "func_name" << "   " << "function service name in function computing cluster." << std::endl
        << std::endl;
    return 0;
}

}
}
