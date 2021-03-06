#ifndef _NAVAGRAHA_JNI_FUNC_H
#define _NAVAGRAHA_JNI_FUNC_H
#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Func_up(JNIEnv * env,
                                             jobject self,
                                             jobject j_cfg,
                                             jobject j_func_up);

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Func_down(JNIEnv * env,
                                               jobject self,
                                               jobject j_cfg,
                                               jobject j_func_down);

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Func_repo(JNIEnv * env,
                                               jobject self,
                                               jobject j_cfg);

JNIEXPORT jint JNICALL
    Java_indi_gscienty_navagraha_jni_Func_repoRemove(JNIEnv * env,
                                               jobject self,
                                               jobject j_cfg,
                                               jobject j_func_remove);

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Func_list(JNIEnv * env,
                                               jobject self,
                                               jobject j_cfg,
                                               jobject j_func_list);

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Func_podList(JNIEnv * env,
                                                  jobject self,
                                                  jobject j_cfg,
                                                  jobject j_func_pod_list);

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Func_detail(JNIEnv * env,
                                                 jobject self,
                                                 jobject j_cfg,
                                                 jobject j_func_detail);

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Func_autoscaling(JNIEnv * env,
                                                      jobject self,
                                                      jobject j_cfg,
                                                      jobject j_func_autoscaling);

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Func_autoscalingList(JNIEnv * env,
                                                          jobject self,
                                                          jobject j_cfg,
                                                          jobject j_func_autoscaling_list);

#ifdef __cplusplus
}

#endif
#endif
