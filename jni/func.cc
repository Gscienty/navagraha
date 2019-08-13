#include "jni/func.hpp"
#include "jni/string.hpp"
#include "cli/config.hpp"
#include "args/func_up.hpp"

static void jconfig_to_config(JNIEnv * env, navagraha::cli::config * cfg, jobject jcfg);
static void j_func_up_to_func_up_arg(JNIEnv * env, navagraha::args::func_up * func_up_cfg, jobject jcfg);

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Func_up(JNIEnv * env,
                                             jobject self,
                                             jobject j_cfg,
                                             jobject j_func_up)
{
    (void) self;
    navagraha::cli::config cfg;
    navagraha::args::func_up func_up_arg;

    jconfig_to_config(env, &cfg, j_cfg);
    j_func_up_to_func_up_arg(env, &func_up_arg, j_func_up);

    return str2jstring(env, std::string("created"));
}

static void jconfig_to_config(JNIEnv * env, navagraha::cli::config * cfg, jobject jcfg)
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

static void j_func_up_to_func_up_arg(JNIEnv * env, navagraha::args::func_up * func_up_cfg, jobject jent)
{
    jclass arg_cls = env->GetObjectClass(jent);
    jmethodID name_mid = env->GetMethodID(arg_cls, "getName", "()Ljava/lang/String;");
    jmethodID policy_mid = env->GetMethodID(arg_cls, "getPolicy", "()Ljava/lang/String;");
    jmethodID image_mid = env->GetMethodID(arg_cls, "getImage", "()Ljava/lang/String;");
    jmethodID namespace_mid = env->GetMethodID(arg_cls, "getNamespace", "()Ljava/lang/String;");
    jmethodID stateful_mid = env->GetMethodID(arg_cls, "getStateful", "()Z;");
    jmethodID update_mid = env->GetMethodID(arg_cls, "getUpdate", "()Z;");
    jmethodID replicas_mid = env->GetMethodID(arg_cls, "getReplicas", "()I");

    // TODO
}
