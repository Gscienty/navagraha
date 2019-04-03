#include "kubeent/probe.hpp"
#include "extensions/link_serializer.hpp"

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

void probe::serialize(probe & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.exec)
        .add(obj.failure_threshold)
        .add(obj.http_get)
        .add(obj.initial_delay_seconds)
        .add(obj.period_seconds)
        .add(obj.success_threshold)
        .add(obj.tcp_socket)
        .add(obj.timeout_seconds)
        .serialize(str);
}
}
}
