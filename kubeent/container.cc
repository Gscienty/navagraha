#include "kubeent/container.hpp"
#include "extensions/link_serializer.hpp"

namespace navagraha {
namespace kubeent {

char CONTAINER_ARGS[] = "args";
char CONTAINER_COMMAND[] = "command";
char CONTAINER_ENV[] = "env";
char CONTAINER_ENV_FROM[] = "envFrom";
char CONTAINER_IMAGE[] = "image";
char CONTAINER_IMAGE_PULL_POLICY[] = "imagePullPolicy";
char CONTAINER_LIFECYCLE[] = "lifecycle";
char CONTAINER_LIVENESS_PROBE[] = "livenessProbe";
char CONTAINER_NAME[] = "name";
char CONTAINER_PORTS[] = "ports";
char CONTAINER_READINESS_PROBE[] = "readinessProbe";
char CONTAINER_RESOURCES[] = "resources";
char CONTAINER_SECURITY_CONTEXT[] = "securityContext";
char CONTAINER_STDIN[] = "stdin";
char CONTAINER_STDIN_ONCE[] = "stdinOnce";
char CONTAINER_TERMINATION_MESSAGE_PATH[] = "terminationMessagePath";
char CONTAINER_TERMINATION_MESSAGE_POLICY[] = "terminationMessagePolicy";
char CONTAINER_TTY[] = "tty";
char CONTAINER_VOLUME_DEVICES[] = "volumeDevices";
char CONTAINER_VOLUME_MOUNTS[] = "volumeMounts";
char CONTAINER_WORKING_DIR[] = "workingDir";

void container::serialize(container & obj, std::ostringstream & str)
{
    extensions::link_serializer()
        .add(obj.args)
        .add(obj.command)
        .add(obj.env)
        .add(obj.env_from)
        .add(obj.image)
        .add(obj.image_pull_policy)
        .add(obj.lifecycle)
        .add(obj.liveness_probe)
        .add(obj.name)
        .add(obj.ports)
        .add(obj.readiness_probe)
        .add(obj.resources)
        .add(obj.security_context_)
        .add(obj.stdin_)
        .add(obj.stdin_once)
        .add(obj.termination_message_path)
        .add(obj.termination_message_policy)
        .add(obj.tty)
        .add(obj.volume_devices)
        .add(obj.volume_mounts)
        .add(obj.working_dir)
        .serialize(str);
}
}
}
