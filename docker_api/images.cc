#include "docker_api/images.hpp"

namespace navagraha {
namespace docker_api {


images::images(CURL * curl)
    : http_client::unix_socket_client(curl)
{

}


extensions::special_list<dockerent::image> images::list()
{
    return this->get_call<extensions::special_list<dockerent::image>>("/images/json");
}

}
}
