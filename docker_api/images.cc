#include "docker_api/images.hpp"

namespace navagraha {
namespace docker_api {


images::images(CURL * curl)
    : http_client::unix_socket_client(curl)
{

}


extensions::common_list images::read()
{
    return this->get_call<extensions::common_list>("/images/json");
}

}
}
