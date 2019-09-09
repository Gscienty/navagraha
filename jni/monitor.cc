#include "jni/monitor.hpp"
#include "jni/config.hpp"
#include "jni/string.hpp"
#include "process/monitor.hpp"
#include <sstream>

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Monitor_add(JNIEnv * env,
                                                 jobject self,
                                                 jobject j_cfg,
                                                 jobject j_namespace)
{
    (void) self;
    navagraha::cli::config config;
    jconfig_to_config(env, &config, j_cfg);

    navagraha::process::monitor(config).start(jstring2str(env, static_cast<jstring>(j_namespace)));

    return str2jstring(env, "done");
}

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Monitor_remove(JNIEnv * env,
                                                    jobject self,
                                                    jobject j_cfg,
                                                    jobject j_namespace)
{
    (void) self;
    navagraha::cli::config config;
    jconfig_to_config(env, &config, j_cfg);

    navagraha::process::monitor(config).remove(jstring2str(env, static_cast<jstring>(j_namespace)));

    return str2jstring(env, "done");
}

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Monitor_get(JNIEnv * env,
                                                 jobject self,
                                                 jobject j_cfg,
                                                 jobject j_namespace)
{
    (void) self;
    navagraha::cli::config config;
    jconfig_to_config(env, &config, j_cfg);

    std::ostringstream oss;
    navagraha::process::monitor(config).get(jstring2str(env, static_cast<jstring>(j_namespace))).serialize(oss);
    return str2jstring(env, oss.str());
}

JNIEXPORT jint JNICALL
    Java_indi_gscienty_navagraha_jni_Monitor_nodeCount(JNIEnv * env,
                                                 jobject self,
                                                 jobject j_cfg)
{
    (void) self;
    navagraha::cli::config config;
    jconfig_to_config(env, &config, j_cfg);

    return navagraha::process::monitor(config).node_count();
}

JNIEXPORT jint JNICALL
    Java_indi_gscienty_navagraha_jni_Monitor_namespaceCount(JNIEnv * env,
                                                            jobject self,
                                                            jobject j_cfg)
{
    (void) self;
    navagraha::cli::config config;
    jconfig_to_config(env, &config, j_cfg);

    return navagraha::process::monitor(config).namespace_count();
}

JNIEXPORT jint JNICALL
    Java_indi_gscienty_navagraha_jni_Monitor_funcCount(JNIEnv * env,
                                                       jobject self,
                                                       jobject j_cfg)
{
    (void) self;
    navagraha::cli::config config;
    jconfig_to_config(env, &config, j_cfg);

    return navagraha::process::monitor(config).func_count();
}

JNIEXPORT jint JNICALL
    Java_indi_gscienty_navagraha_jni_Monitor_projectCount(JNIEnv * env,
                                                          jobject self,
                                                          jobject j_cfg)
{
    (void) self;
    navagraha::cli::config config;
    jconfig_to_config(env, &config, j_cfg);

    return navagraha::process::monitor(config).project_count();
}

