#ifndef _NAVAGRAHA_JNI_CONFIG_H
#define _NAVAGRAHA_JNI_CONFIG_H

#include <jni.h>

#ifdef __cplusplus
extern "C"
{
#endif

JNIEXPORT jboolean JNICALL Java_nava_Config_init(JNIEnv * env, jobject self);

JNIEXPORT jboolean JNICALL Java_nava_Config_setCert(JNIEnv * env, jobject self, jstring cert);

JNIEXPORT jboolean JNICALL Java_nava_Config_setKey(JNIEnv * env, jobject self, jstring key);

JNIEXPORT jboolean JNICALL Java_nava_Config_setCA(JNIEnv * env, jobject self, jstring ca);

JNIEXPORT jboolean JNICALL Java_nava_Config_setApiServer(JNIEnv * env, jobject self, jstring api_server);

JNIEXPORT jboolean JNICALL Java_nava_Config_setDockerSock(JNIEnv * env, jobject self, jstring docker_sock);

JNIEXPORT jstring JNICALL Java_nava_Config_getCert(JNIEnv * env, jobject self);

JNIEXPORT jstring JNICALL Java_nava_Config_getKey(JNIEnv * env, jobject self);

JNIEXPORT jstring JNICALL Java_nava_Config_getCA(JNIEnv * env, jobject self);

JNIEXPORT jstring JNICALL Java_nava_Config_getApiServer(JNIEnv * env, jobject self);

JNIEXPORT jstring JNICALL Java_nava_Config_getDockerSock(JNIEnv * env, jobject self);

#ifdef __cplusplus
}
#endif


#endif
