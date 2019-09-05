#include "jni/node.hpp"
#include "jni/config.hpp"
#include "jni/string.hpp"
#include "process/node.hpp"
#include <sstream>

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Node_list(JNIEnv * env,
                                                    jobject self,
                                                    jobject j_cfg)
{
    (void) self;
    navagraha::cli::config cfg;
    
    jconfig_to_config(env, &cfg, j_cfg);

    std::ostringstream oss;
    navagraha::process::node(cfg).list().serialize(oss);

    return str2jstring(env, oss.str());
}
