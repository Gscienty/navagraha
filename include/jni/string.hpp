#ifndef _NAVAGRAHA_JNI_STRING_H
#define _NAVAGRAHA_JNI_STRING_H

#include <jni.h>
#include <string>

JNIEXPORT std::string JNICALL jstring2str(JNIEnv * env, jstring jstr);

JNIEXPORT jstring JNICALL str2jstring(JNIEnv * env, std::string str);

#endif
