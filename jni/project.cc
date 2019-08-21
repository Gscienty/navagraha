#include "jni/project.hpp"
#include "jni/string.hpp"
#include "process/project.hpp"
#include "cli/config.hpp"
#include "jni/config.hpp"

static void jproj_init_to_arg(JNIEnv * env, navagraha::process::project_init_arg * arg, jobject j_proj_init);
static void jproj_build_to_arg(JNIEnv * env, navagraha::process::project_build_arg * arg, jobject & consumer, jobject j_proj_build);

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Project_init(JNIEnv * env,
                                                  jobject self,
                                                  jobject j_proj_init)
{
    (void) self;
    navagraha::cli::config useless;
    navagraha::process::project_init_arg arg;
    jproj_init_to_arg(env, &arg, j_proj_init);

    navagraha::process::project(useless).init(arg);

    return str2jstring(env, "");
}

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Project_build(JNIEnv * env,
                                                   jobject self,
                                                   jobject jconfig,
                                                   jobject j_proj_build)
{
    (void) self;
    navagraha::cli::config config;
    navagraha::process::project_build_arg arg;
    jobject consumer;

    jconfig_to_config(env, &config, jconfig);
    jproj_build_to_arg(env, &arg, consumer, j_proj_build);

    jclass consumer_cls = env->GetObjectClass(consumer);
    jmethodID accept_mid = env->GetMethodID(consumer_cls, "accept", "(Ljava/lang/Object;)V");

    arg.callback = [&consumer, accept_mid, env] (std::string & msg) -> void
    {

        jstring local_str_arg = str2jstring(env, msg);

        env->CallVoidMethod(consumer, accept_mid, static_cast<jobject>(local_str_arg));
    };

    navagraha::process::project(config).build(arg);

    return str2jstring(env, "");
}

static void jproj_init_to_arg(JNIEnv * env, navagraha::process::project_init_arg * arg, jobject j_proj_init)
{
    jclass arg_cls = env->GetObjectClass(j_proj_init);
    jmethodID path_mid = env->GetMethodID(arg_cls, "getPath", "()Ljava/lang/String;");
    jmethodID type_mid = env->GetMethodID(arg_cls, "getCodeType", "()Ljava/lang/String;");
    jmethodID use_local_mid = env->GetMethodID(arg_cls, "getUseLocal", "()Z");
    jmethodID local_template_path_mid = env->GetMethodID(arg_cls, "getLocalTemplatePath", "()Ljava/lang/String;");

    arg->local_template_path = jstring2str(env, static_cast<jstring>(env->CallObjectMethod(j_proj_init, local_template_path_mid)));
    arg->path = jstring2str(env, static_cast<jstring>(env->CallObjectMethod(j_proj_init, path_mid)));
    arg->type = jstring2str(env, static_cast<jstring>(env->CallObjectMethod(j_proj_init, type_mid)));
    arg->use_local = env->CallBooleanMethod(j_proj_init, use_local_mid);
}

static void jproj_build_to_arg(JNIEnv * env, navagraha::process::project_build_arg * arg, jobject & consumer, jobject j_proj_build)
{
    jclass arg_cls = env->GetObjectClass(j_proj_build);
    
    jmethodID name_mid = env->GetMethodID(arg_cls, "getName", "()Ljava/lang/String;");
    jmethodID version_mid = env->GetMethodID(arg_cls, "getVersion", "()Ljava/lang/String;");
    jmethodID path_mid = env->GetMethodID(arg_cls, "getPath", "()Ljava/lang/String;");
    jmethodID consumer_mid = env->GetMethodID(arg_cls, "getConsumer", "()Ljava/util/function/Consumer;");

    arg->name = jstring2str(env, static_cast<jstring>(env->CallObjectMethod(j_proj_build, name_mid)));
    arg->version = jstring2str(env, static_cast<jstring>(env->CallObjectMethod(j_proj_build, version_mid)));
    arg->path = jstring2str(env, static_cast<jstring>(env->CallObjectMethod(j_proj_build, path_mid)));

    consumer = env->CallObjectMethod(j_proj_build, consumer_mid);
}
