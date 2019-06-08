#ifndef _NAVAGRAHA_KUBEENT_PROBE_H
#define _NAVAGRAHA_KUBEENT_PROBE_H

#include "extensions/field.hpp"
#include "extensions/serializer_helper.hpp"
#include "extensions/serializable.hpp"
#include "kubeent/exec_action.hpp"
#include "kubeent/http_get_action.hpp"
#include "kubeent/tcp_socket_action.hpp"

namespace navagraha {
namespace kubeent {

extern char PROBE_EXEC[];
extern char PROBE_FAILURE_THRESHOLD[];
extern char PROBE_HTTP_GET[];
extern char PROBE_INITIAL_DELAY_SECONDS[];
extern char PROBE_PERIOD_SECONDS[];
extern char PROBE_SUCCESS_THRESHOLD[];
extern char PROBE_TCP_SOCKET[];
extern char PROBE_TIMEOUT_SECONDS[];

class probe : public extensions::serializable<probe> {
public:
    extensions::field<exec_action, PROBE_EXEC> exec;
    extensions::field<int, PROBE_FAILURE_THRESHOLD> failure_threshold;
    extensions::field<http_get_action, PROBE_HTTP_GET> http_get;
    extensions::field<int, PROBE_INITIAL_DELAY_SECONDS> initial_delay_seconds;
    extensions::field<int, PROBE_PERIOD_SECONDS> period_seconds;
    extensions::field<int, PROBE_SUCCESS_THRESHOLD> success_threshold;
    extensions::field<tcp_socket_action, PROBE_TCP_SOCKET> tcp_socket;
    extensions::field<int, PROBE_TIMEOUT_SECONDS> timeout_seconds;

    void bind(extensions::serializer_helper & helper);
};
}
}

#endif
