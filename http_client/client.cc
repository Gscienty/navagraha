#include "http_client/client.hpp"
#include <iostream>

namespace navagraha {
namespace http_client {

client::client(CURL * curl, const std::string host)
    : curl(curl)
    , host(host)
    , binary_payload(NULL)
    , binary_payload_length(0)
{

}

client::~client()
{
    curl_easy_cleanup(this->curl);
}

std::string client::uri(const std::string path) const
{
    return this->host + path;
}

void client::curl_abstract_process(const std::string path, const char * method, http_response & response)
{
    curl_slist * headers = NULL;
    const std::string uri = this->uri(path);
    curl_easy_setopt(this->curl, CURLOPT_URL, uri.c_str());
    response.set_write_func(this->curl);
    curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, method);

    if (this->payload.size() != 0 || this->binary_payload_length != 0)
    {
        if (this->content_type.empty()) {
            headers = curl_slist_append(headers, "Content-Type: application/json; charset=UTF-8");
        }
        else {
            headers = curl_slist_append(headers, ("Content-Type: " + this->content_type).c_str());
        }
        curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER, headers);
        if (this->payload.size() != 0) {
            curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, this->payload.c_str());
            curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE, this->payload.size());
        }
        else {
            curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, this->binary_payload);
            curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE, this->binary_payload_length);
        }
    }

    curl_easy_perform(this->curl);

    if (headers != NULL) {
        curl_slist_free_all(headers);
    }
}

client & client::set_content_type(std::string content_type)
{
    this->content_type = content_type;
    return *this;
}

void client::set_binary_content(std::string & val)
{
    this->binary_payload = val.c_str();
    this->binary_payload_length = val.size();
}

client & client::set_receive_cb(std::function<void (std::string &)> cb)
{
    this->receive_cb = cb;

    return *this;
}

http_response && client::get_request(const std::string path)
{
    http_response ret;
    this->curl_abstract_process(path, "GET", ret);
    return std::move(ret);
}

http_response && client::put_request(const std::string path)
{
    http_response ret;
    this->curl_abstract_process(path, "PUT", ret);
    return std::move(ret);
}

http_response && client::delete_request(const std::string path)
{
    http_response ret;
    this->curl_abstract_process(path, "DELETE", ret);
    return std::move(ret);
}

http_response && client::post_request(const std::string path)
{
    http_response ret;
    this->curl_abstract_process(path, "POST", ret);
    return std::move(ret);
}

http_response && client::patch_request(const std::string path)
{
    http_response ret;
    this->curl_abstract_process(path, "PATCH", ret);
    return std::move(ret);
}

}
}
