#include "jni/func.hpp"
#include "jni/string.hpp"
#include "jni/config.hpp"
#include "cli/config.hpp"
#include "process/func.hpp"
#include "docker_api/images.hpp"
#include "extensions/special_list.hpp"
#include <map>
#include <list>
#include <algorithm>

static void jfunc_up_to_arg(JNIEnv * env, navagraha::process::func_up_arg * func_up_cfg, jobject jent);
static void jfunc_down_to_arg(JNIEnv * env, navagraha::process::func_down_arg * func_down_cfg, jobject jent);
static void jfunc_list_to_arg(JNIEnv * env, navagraha::process::func_list_arg * func_list_cfg, jobject jent);
static void jfunc_pod_list_to_arg(JNIEnv * env, navagraha::process::func_pod_list_arg * func_pod_list_cfg, jobject jent);
static void jfunc_autoscaling_to_arg(JNIEnv * env, navagraha::process::func_autoscaling_arg * func_autoscaling_cfg, jobject jent);
static void jfunc_autoscaling_list_to_arg(JNIEnv * env, navagraha::process::func_autoscaling_list_arg * func_autoscaling_list_cfg, jobject jent);

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Func_up(JNIEnv * env,
                                             jobject self,
                                             jobject j_cfg,
                                             jobject j_func_up)
{
    (void) self;
    navagraha::cli::config cfg;
    navagraha::process::func_up_arg func_up_arg;

    jconfig_to_config(env, &cfg, j_cfg);
    jfunc_up_to_arg(env, &func_up_arg, j_func_up);

    navagraha::process::func(cfg).up(func_up_arg);

    return str2jstring(env, std::string("created"));
}

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Func_down(JNIEnv * env,
                                               jobject self,
                                               jobject j_cfg,
                                               jobject j_func_down)
{
    (void) self;
    navagraha::cli::config cfg;
    navagraha::process::func_down_arg func_down_arg;

    jconfig_to_config(env, &cfg, j_cfg);
    jfunc_down_to_arg(env, &func_down_arg, j_func_down);

    navagraha::process::func(cfg).down(func_down_arg);

    return str2jstring(env, std::string("deleted"));
}

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Func_repo(JNIEnv * env,
                                               jobject self,
                                               jobject j_cfg)
{
    (void) self;
    navagraha::cli::config cfg;

    jconfig_to_config(env, &cfg, j_cfg);

    std::ostringstream oss;
    navagraha::process::func(cfg).repo().serialize(oss);

    return str2jstring(env, oss.str());
}

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Func_list(JNIEnv * env,
                                               jobject self,
                                               jobject j_cfg,
                                               jobject j_func_list)
{
    (void) self;
    navagraha::cli::config cfg;
    navagraha::process::func_list_arg arg;

    jconfig_to_config(env, &cfg, j_cfg);
    jfunc_list_to_arg(env, &arg, j_func_list);

    std::ostringstream oss;
    navagraha::process::func(cfg).list(arg).serialize(oss);

    return str2jstring(env, oss.str());
}

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Func_autoscaling(JNIEnv * env,
                                                      jobject self,
                                                      jobject j_cfg,
                                                      jobject j_func_autoscaling)
{
    (void) self;
    navagraha::cli::config cfg;
    navagraha::process::func_autoscaling_arg arg;

    jconfig_to_config(env, &cfg, j_cfg);
    jfunc_autoscaling_to_arg(env, &arg, j_func_autoscaling);

    navagraha::process::func(cfg).autoscaling(arg);

    return str2jstring(env, std::string("created"));
}

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Func_podList(JNIEnv * env,
                                                  jobject self,
                                                  jobject j_cfg,
                                                  jobject j_func_pod_list)
{
    (void) self;
    navagraha::cli::config cfg;
    navagraha::process::func_pod_list_arg arg;

    jconfig_to_config(env, &cfg, j_cfg);
    jfunc_pod_list_to_arg(env, &arg, j_func_pod_list);

    std::ostringstream oss;
    navagraha::process::func(cfg).list_pod(arg).serialize(oss);
    return str2jstring(env, oss.str());
}

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Func_autoscalingList(JNIEnv * env,
                                                          jobject self,
                                                          jobject j_cfg,
                                                          jobject j_func_autoscaling_list)
{
    (void) self;
    navagraha::cli::config cfg;
    navagraha::process::func_autoscaling_list_arg arg;

    jconfig_to_config(env, &cfg, j_cfg);
    jfunc_autoscaling_list_to_arg(env, &arg, j_func_autoscaling_list);

    std::ostringstream oss;
    navagraha::process::func(cfg).list_autoscaling(arg).serialize(oss);
    return str2jstring(env, oss.str());
}

static void jfunc_up_to_arg(JNIEnv * env, navagraha::process::func_up_arg * func_up_cfg, jobject jent)
{
    jclass arg_cls = env->GetObjectClass(jent);
    jmethodID name_mid = env->GetMethodID(arg_cls, "getName", "()Ljava/lang/String;");
    jmethodID policy_mid = env->GetMethodID(arg_cls, "getPolicy", "()Ljava/lang/String;");
    jmethodID image_mid = env->GetMethodID(arg_cls, "getImage", "()Ljava/lang/String;");
    jmethodID namespace_mid = env->GetMethodID(arg_cls, "getNamespace", "()Ljava/lang/String;");
    jmethodID stateful_mid = env->GetMethodID(arg_cls, "getStateful", "()Z");
    jmethodID update_mid = env->GetMethodID(arg_cls, "getUpdate", "()Z");
    jmethodID replicas_mid = env->GetMethodID(arg_cls, "getReplicas", "()I");

    jstring name_jstr = static_cast<jstring>(env->CallObjectMethod(jent, name_mid));
    jstring policy_jstr = static_cast<jstring>(env->CallObjectMethod(jent, policy_mid));
    jstring image_jstr = static_cast<jstring>(env->CallObjectMethod(jent, image_mid));
    jstring namespace_jstr = static_cast<jstring>(env->CallObjectMethod(jent, namespace_mid));
    jboolean stateful_jbool = env->CallBooleanMethod(jent, stateful_mid);
    jboolean update_jbool = env->CallBooleanMethod(jent, update_mid);
    jint replicas_jint = env->CallIntMethod(jent, replicas_mid);

    func_up_cfg->name = jstring2str(env, name_jstr);
    func_up_cfg->policy = jstring2str(env, policy_jstr);
    func_up_cfg->namespace_ = jstring2str(env, namespace_jstr);
    func_up_cfg->image = jstring2str(env, image_jstr);
    func_up_cfg->stateful = stateful_jbool;
    func_up_cfg->update = update_jbool;
    func_up_cfg->replicas = replicas_jint;
}

static void jfunc_down_to_arg(JNIEnv * env, navagraha::process::func_down_arg * func_down_cfg, jobject jent)
{
    jclass arg_cls = env->GetObjectClass(jent);
    jmethodID namespace_mid = env->GetMethodID(arg_cls, "getNamespace", "()Ljava/lang/String;");
    jmethodID name_mid = env->GetMethodID(arg_cls, "getName", "()Ljava/lang/String;");
    jmethodID stateful_mid = env->GetMethodID(arg_cls, "getStateful", "()Z");

    func_down_cfg->namespace_ = jstring2str(env, static_cast<jstring>(env->CallObjectMethod(jent, namespace_mid)));
    func_down_cfg->name = jstring2str(env, static_cast<jstring>(env->CallObjectMethod(jent, name_mid)));
    func_down_cfg->stateful = env->CallBooleanMethod(jent, stateful_mid);
}

static void jfunc_list_to_arg(JNIEnv * env, navagraha::process::func_list_arg * func_list_cfg, jobject jent)
{
    jclass arg_cls = env->GetObjectClass(jent);
    jmethodID namespace_mid = env->GetMethodID(arg_cls, "getNamespace", "()Ljava/lang/String;");

    func_list_cfg->namespace_ = jstring2str(env, static_cast<jstring>(env->CallObjectMethod(jent, namespace_mid)));
}

static void jfunc_pod_list_to_arg(JNIEnv * env, navagraha::process::func_pod_list_arg * func_pod_list_cfg, jobject jent)
{
    jclass arg_cls = env->GetObjectClass(jent);
    jmethodID name_mid = env->GetMethodID(arg_cls, "getName", "()Ljava/lang/String;");
    jmethodID namespace_mid = env->GetMethodID(arg_cls, "getNamespace", "()Ljava/lang/String;");

    func_pod_list_cfg->name = jstring2str(env, static_cast<jstring>(env->CallObjectMethod(jent, name_mid)));
    func_pod_list_cfg->namespace_ = jstring2str(env, static_cast<jstring>(env->CallObjectMethod(jent, namespace_mid)));
}

static void jfunc_autoscaling_to_arg(JNIEnv * env, navagraha::process::func_autoscaling_arg * func_autoscaling_cfg, jobject jent)
{
    jclass arg_cls = env->GetObjectClass(jent);
    jmethodID name_mid = env->GetMethodID(arg_cls, "getName", "()Ljava/lang/String;");
    jmethodID namespace_mid = env->GetMethodID(arg_cls, "getNamespace", "()Ljava/lang/String;");
    jmethodID cpu_mid = env->GetMethodID(arg_cls, "getCpu", "()I");
    jmethodID min_mid = env->GetMethodID(arg_cls, "getMin", "()I");
    jmethodID max_mid = env->GetMethodID(arg_cls, "getMax", "()I");

    func_autoscaling_cfg->name = jstring2str(env, static_cast<jstring>(env->CallObjectMethod(jent, name_mid)));
    func_autoscaling_cfg->namespace_ = jstring2str(env, static_cast<jstring>(env->CallObjectMethod(jent, namespace_mid)));
    func_autoscaling_cfg->cpu = env->CallIntMethod(jent, cpu_mid);
    func_autoscaling_cfg->min = env->CallIntMethod(jent, min_mid);
    func_autoscaling_cfg->max = env->CallIntMethod(jent, max_mid);
}

static void jfunc_autoscaling_list_to_arg(JNIEnv * env, navagraha::process::func_autoscaling_list_arg * func_autoscaling_list_cfg, jobject jent)
{
    jclass arg_cls = env->GetObjectClass(jent);
    jmethodID name_mid = env->GetMethodID(arg_cls, "getName", "()Ljava/lang/String;");
    jmethodID namespace_mid = env->GetMethodID(arg_cls, "getNamespace", "()Ljava/lang/String;");

    func_autoscaling_list_cfg->name = jstring2str(env, static_cast<jstring>(env->CallObjectMethod(jent, name_mid)));
    func_autoscaling_list_cfg->namespace_ = jstring2str(env, static_cast<jstring>(env->CallObjectMethod(jent, namespace_mid)));
}
