#ifndef _NAVAGRAHA_JNI_NODE_H
#define _NAVAGRAHA_JNI_NODE_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Node_list(JNIEnv * env,
                                                    jobject self,
                                                    jobject j_cfg);

#ifdef __cplusplus
}
#endif

#endif
