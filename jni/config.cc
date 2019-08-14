#include "jni/config.hpp"
#include "jni/string.hpp"

void jconfig_to_config(JNIEnv * env, navagraha::cli::config * cfg, jobject jcfg)
{
    jclass cfg_cls = env->GetObjectClass(jcfg);
    jmethodID ca_mid = env->GetMethodID(cfg_cls, "getCa", "()Ljava/lang/String;");
    jmethodID cert_mid = env->GetMethodID(cfg_cls, "getCert", "()Ljava/lang/String;");
    jmethodID key_mid = env->GetMethodID(cfg_cls, "getKey", "()Ljava/lang/String;");
    jmethodID api_server_mid = env->GetMethodID(cfg_cls, "getApiServer", "()Ljava/lang/String;");
    jmethodID docker_sock_mid = env->GetMethodID(cfg_cls, "getDockerSock", "()Ljava/lang/String;");

    jstring ca_jstr = static_cast<jstring>(env->CallObjectMethod(jcfg, ca_mid));
    jstring cert_jstr = static_cast<jstring>(env->CallObjectMethod(jcfg, cert_mid));
    jstring key_jstr = static_cast<jstring>(env->CallObjectMethod(jcfg, key_mid));
    jstring api_server_jstr = static_cast<jstring>(env->CallObjectMethod(jcfg, api_server_mid));
    jstring docker_sock_jstr = static_cast<jstring>(env->CallObjectMethod(jcfg, docker_sock_mid));

    cfg->kube_ca = jstring2str(env, ca_jstr);
    cfg->kube_cert = jstring2str(env, cert_jstr);
    cfg->kube_key = jstring2str(env, key_jstr);
    cfg->kube_api_server = jstring2str(env, api_server_jstr);
    cfg->docker_sock = jstring2str(env, docker_sock_jstr);
}
