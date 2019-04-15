#include "kube_api/namespaces.hpp"

#include <iostream>

namespace navagraha {
namespace kube_api {

namespaces::namespaces(CURL * curl, const std::string base_uri)
    : http_client::client(curl, base_uri)
{

}

void namespaces::get(std::string name)
{
    std::string & payload = this->get_call("/api/v1/namespaces/" + name);

    // TODO deserialize namespace
}

}
}
