#include "kubeent/service_account.hpp"

namespace navagraha {
namespace kubeent {

char SERVICE_ACCOUNT_API_VERSION[] = "apiVersion";
char SERVICE_ACCOUNT_AUTOMOUNT_SERVICE_ACCOUNT_TOKEN[] = "automountServiceAccountToken";
char SERVICE_ACCOUNT_IMAGE_PULL_SECRETS[] = "imagePullSecrets";
char SERVICE_ACCOUNT_KIND[] = "kind";
char SERVICE_ACCOUNT_METADATA[] = "metadata";
char SERVICE_ACCOUNT_SECRETS[] = "secrets";

void service_account::bind(extensions::serializer_helper & helper)
{
    helper
        .add(this->api_version)
        .add(this->automount_service_account_token)
        .add(this->image_pull_secrets)
        .add(this->kind)
        .add(this->metadata)
        .add(this->secrets);
}

}
}
