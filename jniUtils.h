//
// Created by will on 12/27/23.
//

#ifndef ONSCRIPTER_EN_JNIUTILS_H
#define ONSCRIPTER_EN_JNIUTILS_H
#include <jni.h>

void JNI_SetWindowTitle(const char* title);

void JNI_SetSkipMode(int skip_mode);

void JNI_SetAutomode(bool automode);

void JNI_SetOnsPtr(void* ptr);

#endif //ONSCRIPTER_EN_JNIUTILS_H
