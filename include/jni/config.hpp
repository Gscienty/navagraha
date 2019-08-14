#ifndef _NAVAGRAHA_JNI_CONFIG_H
#define _NAVAGRAHA_JNI_CONFIG_H

#include <jni.h>
#include "cli/config.hpp"

void jconfig_to_config(JNIEnv * env, navagraha::cli::config * cfg, jobject jcfg);

#endif
