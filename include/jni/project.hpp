#ifndef _NAVAGRAHA_JNI_PROJECT_H
#define _NAVAGRAHA_JNI_PROJECT_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Project_init(JNIEnv * env,
                                                  jobject self,
                                                  jobject j_proj_init);

JNIEXPORT jstring JNICALL
    Java_indi_gscienty_navagraha_jni_Project_build(JNIEnv * env,
                                                   jobject self,
                                                   jobject jconfig,
                                                   jobject j_proj_init);

#ifdef __cplusplus
}
#endif

#endif
