#include "jni/gateway.hpp"
#include "jni/config.hpp"
#include "jni/string.hpp"
#include "process/gateway.hpp"

static void jgateway_set_to_arg(JNIEnv * env, navagraha::process::gateway_set_arg * arg, jobject j_gateway_cfg);
static void jgateway_get_to_arg(JNIEnv * env, navagraha::process::gateway_get_arg * arg, jobject j_gateway_cfg);
static void jgateway_remove_to_arg(JNIEnv * env, navagraha::process::gateway_remove_arg * arg, jobject j_gateway_cfg);

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Gateway_set(JNIEnv * env,
                                                 jobject self,
                                                 jobject j_cfg,
                                                 jobject j_gateway_cfg)
{
    (void) self;
    navagraha::cli::config cfg;
    navagraha::process::gateway_set_arg arg;

    jconfig_to_config(env, &cfg, j_cfg);
    jgateway_set_to_arg(env, &arg, j_gateway_cfg);

    navagraha::process::gateway(cfg).set(arg);
    return str2jstring(env, std::string(""));
}

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Gateway_get(JNIEnv * env,
                                                 jobject self,
                                                 jobject j_cfg,
                                                 jobject j_gateway_cfg)
{
    (void) self;
    navagraha::cli::config cfg;
    navagraha::process::gateway_get_arg arg;

    jconfig_to_config(env, &cfg, j_cfg);
    jgateway_get_to_arg(env, &arg, j_gateway_cfg);

    std::ostringstream oss;
    navagraha::process::gateway(cfg).get(arg).serialize(oss);
    return str2jstring(env, oss.str());
}

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Gateway_remove(JNIEnv * env,
                                                    jobject self,
                                                    jobject j_cfg,
                                                    jobject j_gateway_cfg)
{
    (void) self;
    navagraha::cli::config cfg;
    navagraha::process::gateway_remove_arg arg;

    jconfig_to_config(env, &cfg, j_cfg);
    jgateway_remove_to_arg(env, &arg, j_gateway_cfg);

    navagraha::process::gateway(cfg).remove(arg);
    return str2jstring(env, std::string());
}

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Gateway_repo(JNIEnv * env,
                                                  jobject self,
                                                  jobject j_cfg)
{
    (void) self;
    navagraha::cli::config cfg;
    jconfig_to_config(env, &cfg, j_cfg);

    std::ostringstream oss;
    navagraha::process::gateway(cfg).repo().serialize(oss);
    return str2jstring(env, oss.str());
}

static void jgateway_set_to_arg(JNIEnv * env, navagraha::process::gateway_set_arg * arg, jobject j_gateway_cfg)
{
    jclass arg_cls = env->GetObjectClass(j_gateway_cfg);
    jmethodID namespace_mid = env->GetMethodID(arg_cls, "getNamespace", "()Ljava/lang/String;");
    jmethodID policy_mid = env->GetMethodID(arg_cls, "getPolicy", "()Ljava/lang/String;");
    jmethodID replicas_mid = env->GetMethodID(arg_cls, "getReplicas", "()I");
    jmethodID image_mid = env->GetMethodID(arg_cls, "getImage", "()Ljava/lang/String;");

    arg->namespace_ = jstring2str(env, static_cast<jstring>(env->CallObjectMethod(j_gateway_cfg, namespace_mid)));
    arg->policy = jstring2str(env, static_cast<jstring>(env->CallObjectMethod(j_gateway_cfg, policy_mid)));
    arg->image = jstring2str(env, static_cast<jstring>(env->CallObjectMethod(j_gateway_cfg, image_mid)));
    arg->replicas = env->CallIntMethod(j_gateway_cfg, replicas_mid);
}

static void jgateway_get_to_arg(JNIEnv * env, navagraha::process::gateway_get_arg * arg, jobject j_gateway_cfg)
{
    jclass arg_cls = env->GetObjectClass(j_gateway_cfg);
    jmethodID namespace_mid = env->GetMethodID(arg_cls, "getNamespace", "()Ljava/lang/String;");

    arg->namespace_ = jstring2str(env, static_cast<jstring>(env->CallObjectMethod(j_gateway_cfg, namespace_mid)));
}

static void jgateway_remove_to_arg(JNIEnv * env, navagraha::process::gateway_remove_arg * arg, jobject j_gateway_cfg)
{
    jclass arg_cls = env->GetObjectClass(j_gateway_cfg);
    jmethodID namespace_mid = env->GetMethodID(arg_cls, "getNamespace", "()Ljava/lang/String;");

    arg->namespace_ = jstring2str(env, static_cast<jstring>(env->CallObjectMethod(j_gateway_cfg, namespace_mid)));
}

