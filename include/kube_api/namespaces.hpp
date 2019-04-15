#ifndef _NAVAGRAHA_KUBE_API_NAMESPACES_H
#define _NAVAGRAHA_KUBE_API_NAMESPACES_H

#include "http_client/client.hpp"

namespace navagraha {
namespace kube_api {

class namespaces : public http_client::client {
public:
    namespaces(CURL * curl, const std::string base_uri);

    void read(std::string name);

    void list();
};

}
}

#endif
