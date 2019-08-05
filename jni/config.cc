#include "jni/config.hpp"
#include "cli/config.hpp"
#include "jni/string.hpp"

static jfieldID get_config_pointer_fid(JNIEnv * env, jobject self);

static int config_init(JNIEnv * env, jobject self);

static int config_set_cert(JNIEnv * env, jobject self, std::string cert);
static int config_set_key(JNIEnv * env, jobject self, std::string key);
static int config_set_ca(JNIEnv * env, jobject self, std::string ca);
static int config_set_api_server(JNIEnv * env, jobject self, std::string api_server);
static int config_set_docker_sock(JNIEnv * env, jobject self, std::string docker_sock);

static std::string config_get_cert(JNIEnv * env, jobject self);
static std::string config_get_key(JNIEnv * env, jobject self);
static std::string config_get_ca(JNIEnv * env, jobject self);
static std::string config_get_api_server(JNIEnv * env, jobject self);
static std::string config_get_docker_sock(JNIEnv * env, jobject self);

JNIEXPORT jboolean JNICALL Java_nava_Config_init(JNIEnv * env, jobject self)
{
    return config_init(env, self) == 0;
}

JNIEXPORT jboolean JNICALL Java_nava_Config_setCert(JNIEnv * env, jobject self, jstring cert)
{
    return config_set_cert(env, self, jstring2str(env, cert)) == 0;
}

JNIEXPORT jboolean JNICALL Java_nava_Config_setKey(JNIEnv * env, jobject self, jstring key)
{
    return config_set_key(env, self, jstring2str(env, key)) == 0;
}

JNIEXPORT jboolean JNICALL Java_nava_Config_setCA(JNIEnv * env, jobject self, jstring ca)
{
    return config_set_ca(env, self, jstring2str(env, ca)) == 0;
}

JNIEXPORT jboolean JNICALL Java_nava_Config_setApiServer(JNIEnv * env, jobject self, jstring api_server)
{
    return config_set_api_server(env, self, jstring2str(env, api_server)) == 0;
}

JNIEXPORT jboolean JNICALL Java_nava_Config_setDockerSock(JNIEnv * env, jobject self, jstring docker_sock)
{
    return config_set_docker_sock(env, self, jstring2str(env, docker_sock)) == 0;
}

JNIEXPORT jstring JNICALL Java_nava_Config_getCert(JNIEnv * env, jobject self)
{
    return str2jstring(env, config_get_cert(env, self));
}

JNIEXPORT jstring JNICALL Java_nava_Config_getKey(JNIEnv * env, jobject self)
{
    return str2jstring(env, config_get_key(env, self));
}

JNIEXPORT jstring JNICALL Java_nava_Config_getCA(JNIEnv * env, jobject self)
{
    return str2jstring(env, config_get_ca(env, self));
}

JNIEXPORT jstring JNICALL Java_nava_Config_getApiServer(JNIEnv * env, jobject self)
{
    return str2jstring(env, config_get_api_server(env, self));
}

JNIEXPORT jstring JNICALL Java_nava_Config_getDockerSock(JNIEnv * env, jobject self)
{
    return str2jstring(env, config_get_docker_sock(env, self));
}

static jfieldID get_config_pointer_fid(JNIEnv * env, jobject self)
{
    jclass clazz = env->GetObjectClass(self);
    return env->GetFieldID(clazz, "configPointer", "I");
}

static int config_init(JNIEnv * env, jobject self)
{
    using namespace navagraha::cli;

    config * cfg = new config();
    if (cfg == NULL) {
        return -1;
    }
    env->SetLongField(self, get_config_pointer_fid(env, self), reinterpret_cast<const long>(cfg));
    return 0;
}

static int config_set_cert(JNIEnv * env, jobject self, std::string cert)
{
    using namespace navagraha::cli;

    config * cfg = reinterpret_cast<config *>(env->GetLongField(self, get_config_pointer_fid(env, self)));
    if (cfg == nullptr) {
        return -1;
    }
    cfg->kube_cert = cert;
    return 0;
}

static int config_set_key(JNIEnv * env, jobject self, std::string key)
{
    using namespace navagraha::cli;

    config * cfg = reinterpret_cast<config *>(env->GetLongField(self, get_config_pointer_fid(env, self)));
    if (cfg == nullptr) {
        return -1;
    }
    cfg->kube_key = key;
    return 0;
}

static int config_set_ca(JNIEnv * env, jobject self, std::string ca)
{
    using namespace navagraha::cli;

    config * cfg = reinterpret_cast<config *>(env->GetLongField(self, get_config_pointer_fid(env, self)));
    if (cfg == nullptr) {
        return -1;
    }
    cfg->kube_ca = ca;
    return 0;
}

static int config_set_api_server(JNIEnv * env, jobject self, std::string api_server)
{
    using namespace navagraha::cli;

    config * cfg = reinterpret_cast<config *>(env->GetLongField(self, get_config_pointer_fid(env, self)));
    if (cfg == nullptr) {
        return -1;
    }
    cfg->kube_api_server = api_server;
    return 0;
}

static int config_set_docker_sock(JNIEnv * env, jobject self, std::string docker_sock)
{
    using namespace navagraha::cli;

    config * cfg = reinterpret_cast<config *>(env->GetLongField(self, get_config_pointer_fid(env, self)));
    if (cfg == nullptr) {
        return -1;
    }
    cfg->docker_sock = docker_sock;
    return 0;
}

static std::string config_get_cert(JNIEnv * env, jobject self)
{
    using namespace navagraha::cli;

    config * cfg = reinterpret_cast<config *>(env->GetLongField(self, get_config_pointer_fid(env, self)));
    if (cfg == nullptr) {
        return std::string();
    }
    return cfg->kube_cert;
}

static std::string config_get_key(JNIEnv * env, jobject self)
{
    using namespace navagraha::cli;

    config * cfg = reinterpret_cast<config *>(env->GetLongField(self, get_config_pointer_fid(env, self)));
    if (cfg == nullptr) {
        return std::string();
    }
    return cfg->kube_key;
}

static std::string config_get_ca(JNIEnv * env, jobject self)
{
    using namespace navagraha::cli;

    config * cfg = reinterpret_cast<config *>(env->GetLongField(self, get_config_pointer_fid(env, self)));
    if (cfg == nullptr) {
        return std::string();
    }
    return cfg->kube_ca;
}

static std::string config_get_api_server(JNIEnv * env, jobject self)
{
    using namespace navagraha::cli;

    config * cfg = reinterpret_cast<config *>(env->GetLongField(self, get_config_pointer_fid(env, self)));
    if (cfg == nullptr) {
        return std::string();
    }
    return cfg->kube_api_server;
}

static std::string config_get_docker_sock(JNIEnv * env, jobject self)
{
    using namespace navagraha::cli;

    config * cfg = reinterpret_cast<config *>(env->GetLongField(self, get_config_pointer_fid(env, self)));
    if (cfg == nullptr) {
        return std::string();
    }
    return cfg->docker_sock;
}
