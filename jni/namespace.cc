#include "jni/namespace.hpp"
#include "jni/config.hpp"
#include "jni/string.hpp"
#include "process/namespace.hpp"
#include <sstream>

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Namespace_list(JNIEnv * env,
                                                    jobject self,
                                                    jobject j_cfg)
{
    (void) self;
    navagraha::cli::config cfg;

    jconfig_to_config(env, &cfg, j_cfg);
    std::ostringstream oss;
    navagraha::process::namespace_(cfg).list().serialize(oss);
    return str2jstring(env, oss.str());
}

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Namespace_add(JNIEnv * env,
                                                   jobject self,
                                                   jobject j_cfg,
                                                   jstring j_namespace)
{
    (void) self;
    navagraha::cli::config cfg;

    jconfig_to_config(env, &cfg, j_cfg);
    navagraha::process::namespace_(cfg).add(jstring2str(env, j_namespace));
    return str2jstring(env, "");
}

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Namespace_remove(JNIEnv * env,
                                                      jobject self,
                                                      jobject j_cfg,
                                                      jstring j_namespace)
{
    (void) self;
    navagraha::cli::config cfg;

    jconfig_to_config(env, &cfg, j_cfg);
    navagraha::process::namespace_(cfg).remove(jstring2str(env, j_namespace));
    return str2jstring(env, "");
}
