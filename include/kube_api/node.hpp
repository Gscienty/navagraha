#ifndef _NAVAGRAHA_KUBE_API_NODE_H
#define _NAVAGRAHA_KUBE_API_NODE_H

#include "http_client/client.hpp"
#include "http_client/http_response.hpp"
#include "kubeent/node.hpp"

namespace navagraha {
namespace kube_api {

class node : public http_client::client {
public:
    node(CURL * curl, const std::string host);

    http_client::http_response read(const std::string name);

    http_client::http_response list();   
};

}
}

#endif
