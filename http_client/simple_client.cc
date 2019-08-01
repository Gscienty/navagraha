#include "http_client/simple_client.hpp"

namespace navagraha {
namespace http_client {

simple_client::simple_client(CURL * curl, const std::string host)
    : client(curl, host)
{

}

http_response simple_client::post_request(const std::string path, std::string payload)
{
    this->set_binary_content(payload);
    return this->client::post_request(path);
}

}
}
