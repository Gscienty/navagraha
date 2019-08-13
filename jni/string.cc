#include "jni/string.hpp"
#include <string.h>

JNIEXPORT std::string JNICALL jstring2str(JNIEnv * env, jstring jstr)
{
    std::string ret;
    jclass jstr_class = env->FindClass("java/lang/String");
    jstring str_encode = env->NewStringUTF("UTF-8");
    jmethodID mid = env->GetMethodID(jstr_class, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray bar = static_cast<jbyteArray>(env->CallObjectMethod(jstr, mid, str_encode));
    jsize len = env->GetArrayLength(bar);
    jbyte * ba = env->GetByteArrayElements(bar, JNI_FALSE);

    if (len > 0) {
        ret.resize(len, 0);
        memcpy(const_cast<char *>(reinterpret_cast<const char *>(ret.data())), reinterpret_cast<const void *>(ba), len);
    }
    env->ReleaseByteArrayElements(bar, ba, 0);

    return ret;
}

JNIEXPORT jstring JNICALL str2jstring(JNIEnv * env, std::string str)
{
    jclass str_class = env->FindClass("Ljava/lang/String;");
    jmethodID ctor_mid = env->GetMethodID(str_class, "<init>", "([BLjava/lang/String;)V");
    jbyteArray bytes = env->NewByteArray(str.size());
    env->SetByteArrayRegion(bytes, 0, str.size(), reinterpret_cast<const jbyte *>(str.data()));
    jstring encoding = env->NewStringUTF("UTF-8");
    
    return static_cast<jstring>(env->NewObject(str_class, ctor_mid, bytes, encoding));
}
