#ifndef _NAVAGRAHA_JNI_MONITOR_H
#define _NAVAGRAHA_JNI_MONITOR_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Monitor_add(JNIEnv * env,
                                                 jobject self,
                                                 jobject j_cfg,
                                                 jobject j_monitor_cfg);

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Monitor_remove(JNIEnv * env,
                                                    jobject self,
                                                    jobject j_cfg,
                                                    jobject j_monitor_cfg);

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Monitor_get(JNIEnv * env,
                                                 jobject self,
                                                 jobject j_cfg,
                                                 jobject j_monitor_cfg);

JNIEXPORT jint JNICALL
    Java_indi_gscienty_navagraha_jni_Monitor_nodeCount(JNIEnv * env,
                                                 jobject self,
                                                 jobject j_cfg);

JNIEXPORT jint JNICALL
    Java_indi_gscienty_navagraha_jni_Monitor_namespaceCount(JNIEnv * env,
                                                            jobject self,
                                                            jobject j_cfg);

JNIEXPORT jint JNICALL
    Java_indi_gscienty_navagraha_jni_Monitor_funcCount(JNIEnv * env,
                                                       jobject self,
                                                       jobject j_cfg);

JNIEXPORT jint JNICALL
    Java_indi_gscienty_navagraha_jni_Monitor_projectCount(JNIEnv * env,
                                                          jobject self,
                                                          jobject j_cfg);

#ifdef __cplusplus
}
#endif

#endif
