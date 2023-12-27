#ifdef __ANDROID__

#include "jniState.h"
#include "ONScripterLabel.h"

extern "C"
JNIEXPORT void JNICALL
Java_org_libsdl_app_JniState_TrySetNormalSkip(JNIEnv *env, jclass clazz, jlong ptr,
jboolean new_value) {
    ONScripterLabel* ons = (ONScripterLabel*)((uintptr_t)ptr);
    ons->TrySetNormalSkip(new_value == JNI_TRUE);
}
extern "C"
JNIEXPORT void JNICALL
Java_org_libsdl_app_JniState_TrySetEopSkip(JNIEnv *env, jclass clazz, jlong ptr,
jboolean new_value) {
    ONScripterLabel* ons = (ONScripterLabel*)((uintptr_t)ptr);
    ons->TrySetEopSkip(new_value == JNI_TRUE);
}
extern "C"
JNIEXPORT void JNICALL
Java_org_libsdl_app_JniState_TrySetAutomode(JNIEnv *env, jclass clazz, jlong ptr,
jboolean new_value) {
    ONScripterLabel* ons = (ONScripterLabel*)((uintptr_t)ptr);
    ons->TrySetAutomode(new_value == JNI_TRUE);
}

#endif //__ANDROID__