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
        << "  " << "up" << "          " << "Go online with the specified function service." << std::endl
        << "  " << "  " << "          " << "usage:" << "  " << "nava func up {func_name} --image {image_name} [--policy {policy_name}] [--namespace {namespace}]"  << std::endl
        << "  " << "  " << "          " << "      " << "  " << "  " << "[--update [--update-type {update_type}]]" << std::endl
        << "  " << "  " << "          " << "  " << "func_name" << "   " << "function service name in function computing cluster." << std::endl
        << "  " << "  " << "          " << "  " << "image_name" << "  " << "docker image name corresponding to function service." << std::endl
        << "  " << "  " << "          " << "  " << "policy_name" << " " << "node pull docker image policy, values: \"Always\"(default), \"IfNotPresent\", \"Never\"" << std::endl
        << "  " << "  " << "          " << "  " << "namespace" << "   " << "namespaces where function services reside" << std::endl
        << "  " << "  " << "          " << "  " << "update_type" << " " << "update method, values: \"Recreate\", \"RollingUpdate\"" << std::endl
        << std::endl
        << "  " << "down" << "        " << "Logoff the specified function service." << std::endl
        << "  " << "    " << "        " << "usage:" << "  " <<  "nava func down {func_name} [--namespace {namespace}]" << std::endl
        << "  " << "    " << "        " << "  " << "func_name" << "   " << "function service name in function computing cluster." << std::endl
        << "  " << "    " << "        " << "  " << "namespace" << "   " << "namespaces where function services reside" << std::endl
        << std::endl
        << "  " << "list" << "        " << "Enumerate all online function services." << std::endl
        << "  " << "    " << "        " << "usage:" << "  " <<  "nava func list [--namespace {namespace}]" << std::endl
        << "  " << "    " << "        " << "  " << "namespace" << "   " << "namespaces where function services reside" << std::endl
        << std::endl
        << "  " << "repo" << "        " << "Enumerate all repository function services." << std::endl
        << "  " << "    " << "        " << "usage:" << "  " <<  "nava func repo [--name {func name}]" << std::endl
        << "  " << "    " << "        " << "  " << "func_name" << "   " << "function service name in function computing cluster." << std::endl
        << std::endl
        << "  " << "autoscaling" << " " << "Enumerate all repository function services." << std::endl
        << "  " << "    " << "        " << "usage:" << "  " <<  "nava func autoscaling {func_name} --cpu {cpu_limit} --min {min} --max{max} [--namespace {func name}]" << std::endl
        << "  " << "    " << "        " << "  " << "func_name" << "   " << "function service name in function computing cluster." << std::endl
        << "  " << "    " << "        " << "  " << "cpu" << "         " << "cpu utilization percentage." << std::endl
        << "  " << "    " << "        " << "  " << "min" << "         " << "function pod min count." << std::endl
        << "  " << "    " << "        " << "  " << "max" << "         " << "function pod max count." << std::endl
        << "  " << "    " << "        " << "  " << "namespace" << "   " << "namespaces where function services reside" << std::endl
        << std::endl;
    return 0;
}

}
}
