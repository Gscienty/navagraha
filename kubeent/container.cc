#include "kubeent/container.hpp"

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

void container::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->args)
        .add(this->command)
        .add(this->env)
        .add(this->env_from)
        .add(this->image)
        .add(this->image_pull_policy)
        .add(this->lifecycle)
        .add(this->liveness_probe)
        .add(this->name)
        .add(this->ports)
        .add(this->readiness_probe)
        .add(this->resources)
        .add(this->security_context_)
        .add(this->stdin_)
        .add(this->stdin_once)
        .add(this->termination_message_path)
        .add(this->termination_message_policy)
        .add(this->tty)
        .add(this->volume_devices)
        .add(this->volume_mounts)
        .add(this->working_dir);
}

}
}
