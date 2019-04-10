#include "kubeent/probe.hpp"

namespace navagraha {
namespace kubeent {

char PROBE_EXEC[] = "exec";
char PROBE_FAILURE_THRESHOLD[] = "failureThreshold";
char PROBE_HTTP_GET[] = "httpGet";
char PROBE_INITIAL_DELAY_SECONDS[] = "initialDelaySeconds";
char PROBE_PERIOD_SECONDS[] = "periodSeconds";
char PROBE_SUCCESS_THRESHOLD[] = "successThreshold";
char PROBE_TCP_SOCKET[] = "tcpSocket";
char PROBE_TIMEOUT_SECONDS[] = "timeoutSeconds";

void probe::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->exec)
        .add(this->failure_threshold)
        .add(this->http_get)
        .add(this->initial_delay_seconds)
        .add(this->period_seconds)
        .add(this->success_threshold)
        .add(this->tcp_socket)
        .add(this->timeout_seconds);
}

}
}
