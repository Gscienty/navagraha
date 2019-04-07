#ifndef _NAVAGRAHA_KUBEENT_SELINUX_OPTIONS_H
#define _NAVAGRAHA_KUBEENT_SELINUX_OPTIONS_H

#include "extensions/field.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char SELINUX_OPTIONS_LEVEL[];
extern char SELINUX_OPTIONS_ROLE[];
extern char SELINUX_OPTIONS_TYPE[];
extern char SELINUX_OPTIONS_USER[];

class selinux_options {
public:
    extensions::field<std::string, SELINUX_OPTIONS_LEVEL> level;
    extensions::field<std::string, SELINUX_OPTIONS_ROLE> role;
    extensions::field<std::string, SELINUX_OPTIONS_TYPE> type;
    extensions::field<std::string, SELINUX_OPTIONS_USER> user;

    static void serialize(selinux_options & obj, std::ostringstream & str);
};

}
}

#endif
