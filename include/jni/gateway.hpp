#ifndef _NAVAGRAHA_JNI_GATEWAY_H
#define _NAVAGRAHA_JNI_GATEWAY_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Gateway_set(JNIEnv * env,
                                                 jobject self,
                                                 jobject j_cfg,
                                                 jobject j_gateway_cfg);

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Gateway_get(JNIEnv * env,
                                                 jobject self,
                                                 jobject j_cfg,
                                                 jobject j_gateway_cfg);

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Gateway_remove(JNIEnv * env,
                                                    jobject self,
                                                    jobject j_cfg,
                                                    jobject j_gateway_cfg);

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Gateway_repo(JNIEnv * env,
                                                  jobject self,
                                                  jobject j_cfg);

#ifdef __cplusplus
}
#endif

#endif
