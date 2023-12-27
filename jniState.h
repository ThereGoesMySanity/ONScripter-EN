#ifndef ONSCRIPTER_EN_JNISTATE_H
#define ONSCRIPTER_EN_JNISTATE_H
#ifdef __ANDROID__
#include <jni.h>
void JNI_SetSkipMode(int skip_mode);

void JNI_SetAutomode(bool automode);

void JNI_SetOnsPtr(void* ptr);
#endif //__ANDROID__

#endif //ONSCRIPTER_EN_JNISTATE_H
