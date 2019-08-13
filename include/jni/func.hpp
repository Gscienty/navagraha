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

#ifdef __cplusplus
}

#endif
#endif
