#ifndef _NAVAGRAHA_JNI_NAMESPACE_H
#define _NAVAGRAHA_JNI_NAMESPACE_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Namespace_list(JNIEnv * env,
                                                    jobject self,
                                                    jobject j_cfg);

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Namespace_add(JNIEnv * env,
                                                   jobject self,
                                                   jobject j_cfg,
                                                   jstring j_namespace);

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Namespace_remove(JNIEnv * env,
                                                      jobject self,
                                                      jobject j_cfg,
                                                      jstring j_namespace);

#ifdef __cplusplus
}
#endif

#endif
