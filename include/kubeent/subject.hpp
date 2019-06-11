#ifndef _NAVAGRAHA_KUBEENT_SUBJECT_H
#define _NAVAGRAHA_KUBEENT_SUBJECT_H

#include "extensions/serializable.hpp"
#include "extensions/field.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char SUBJECT_API_GROUP[];
extern char SUBJECT_KIND[];
extern char SUBJECT_NAME[];
extern char SUBJECT_NAMESPACE[];

class subject : public extensions::serializable<subject> {
public:
    extensions::field<std::string, SUBJECT_API_GROUP> api_group;
    extensions::field<std::string, SUBJECT_KIND> kind;
    extensions::field<std::string, SUBJECT_NAME> name;
    extensions::field<std::string, SUBJECT_NAMESPACE> namespace_;

    void bind(extensions::serializer_helper & helper);
};

}
}

#endif
