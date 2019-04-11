#ifndef _NAVAGRAHA_KUBEENT_CONTAINER_H
#define _NAVAGRAHA_KUBEENT_CONTAINER_H

#include "extensions/field.hpp"
#include "extensions/special_list.hpp"
#include "extensions/serializer_helper.hpp"
#include "kubeent/serializable.hpp"
#include "kubeent/env_var.hpp"
#include "kubeent/env_var_source.hpp"
#include "kubeent/lifecycle.hpp"
#include "kubeent/probe.hpp"
#include "kubeent/container_port.hpp"
#include "kubeent/resource_requirements.hpp"
#include "kubeent/security_context.hpp"
#include "kubeent/volume_mount.hpp"
#include "kubeent/volume_device.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char CONTAINER_ARGS[];
extern char CONTAINER_COMMAND[];
extern char CONTAINER_ENV[];
extern char CONTAINER_ENV_FROM[];
extern char CONTAINER_IMAGE[];
extern char CONTAINER_IMAGE_PULL_POLICY[];
extern char CONTAINER_LIFECYCLE[];
extern char CONTAINER_LIVENESS_PROBE[];
extern char CONTAINER_NAME[];
extern char CONTAINER_PORTS[];
extern char CONTAINER_READINESS_PROBE[];
extern char CONTAINER_RESOURCES[];
extern char CONTAINER_SECURITY_CONTEXT[];
extern char CONTAINER_STDIN[];
extern char CONTAINER_STDIN_ONCE[];
extern char CONTAINER_TERMINATION_MESSAGE_PATH[];
extern char CONTAINER_TERMINATION_MESSAGE_POLICY[];
extern char CONTAINER_TTY[];
extern char CONTAINER_VOLUME_DEVICES[];
extern char CONTAINER_VOLUME_MOUNTS[];
extern char CONTAINER_WORKING_DIR[];

class container : public serializable<container> {
public:
    extensions::field<
        extensions::special_list<std::string>,
        CONTAINER_ARGS> args;
    extensions::field<
        extensions::special_list<std::string>,
        CONTAINER_COMMAND> command;
    extensions::field<
        extensions::special_list<env_var>,
        CONTAINER_ENV> env;
    extensions::field<
        extensions::special_list<env_var_source>,
        CONTAINER_ENV_FROM> env_from;
    extensions::field<std::string, CONTAINER_IMAGE> image;
    extensions::field<std::string, CONTAINER_IMAGE_PULL_POLICY> image_pull_policy;
    extensions::field<lifecycle, CONTAINER_LIFECYCLE> lifecycle_;
    extensions::field<probe, CONTAINER_LIVENESS_PROBE> liveness_probe;
    extensions::field<std::string, CONTAINER_NAME> name;
    extensions::field<
        extensions::special_list<container_port>,
        CONTAINER_PORT_CONTAINER_PORT> ports;
    extensions::field<probe, CONTAINER_READINESS_PROBE> readiness_probe;
    extensions::field<resource_requirements, CONTAINER_RESOURCES> resources;
    extensions::field<security_context, CONTAINER_SECURITY_CONTEXT> security_context_;
    extensions::field<bool, CONTAINER_STDIN> stdin_;
    extensions::field<bool, CONTAINER_STDIN_ONCE> stdin_once;
    extensions::field<std::string, CONTAINER_TERMINATION_MESSAGE_PATH> termination_message_path;
    extensions::field<std::string, CONTAINER_TERMINATION_MESSAGE_POLICY> termination_message_policy;
    extensions::field<bool, CONTAINER_TTY> tty;
    extensions::field<extensions::special_list<volume_device>, CONTAINER_VOLUME_DEVICES> volume_devices;
    extensions::field<extensions::special_list<volume_mount>, CONTAINER_VOLUME_MOUNTS> volume_mounts;
    extensions::field<std::string, CONTAINER_WORKING_DIR> working_dir;

    void bind(extensions::serializer_helper & helper);
};
}
}

#endif
