#ifndef _NAVAGRAHA_KUBEENT_SERVICE_ACCOUNT_H
#define _NAVAGRAHA_KUBEENT_SERVICE_ACCOUNT_H

#include "extensions/serializable.hpp"
#include "extensions/special_list.hpp"
#include "extensions/field.hpp"
#include "kubeent/local_object_reference.hpp"
#include "kubeent/object_reference.hpp"
#include "kubeent/object_meta.hpp"
#include <string>

namespace navagraha {
namespace kubeent {

extern char SERVICE_ACCOUNT_API_VERSION[];
extern char SERVICE_ACCOUNT_AUTOMOUNT_SERVICE_ACCOUNT_TOKEN[];
extern char SERVICE_ACCOUNT_IMAGE_PULL_SECRETS[];
extern char SERVICE_ACCOUNT_KIND[];
extern char SERVICE_ACCOUNT_METADATA[];
extern char SERVICE_ACCOUNT_SECRETS[];

class service_account : public extensions::serializable<service_account> {
public:
    extensions::field<std::string, SERVICE_ACCOUNT_API_VERSION> api_version;
    extensions::field<bool, SERVICE_ACCOUNT_AUTOMOUNT_SERVICE_ACCOUNT_TOKEN> automount_service_account_token;
    extensions::field<extensions::special_list<local_object_reference>, SERVICE_ACCOUNT_IMAGE_PULL_SECRETS> image_pull_secrets;
    extensions::field<std::string, SERVICE_ACCOUNT_KIND> kind;
    extensions::field<object_meta, SERVICE_ACCOUNT_METADATA> metadata;
    extensions::field<extensions::special_list<object_reference>, SERVICE_ACCOUNT_SECRETS> secrets;

    void bind(extensions::serializer_helper & helper);
};

}
}


#endif
