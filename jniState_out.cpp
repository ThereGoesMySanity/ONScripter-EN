#ifdef __ANDROID__

#include "jniState.h"
typedef struct tick_context {
    JavaVM *javaVM;
    JNIEnv *env;
    jclass jniHelperClz;
    jmethodID setSkipMode;
    jmethodID setAutomode;
    jmethodID setOnsPtr;
    int done;
} TickContext;
TickContext g_ctx = {0};

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;

    g_ctx.javaVM = vm;
    if (vm->GetEnv((void **)&env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;  // JNI version not supported.
    }

    jclass clz = env->FindClass("org/libsdl/app/JniState");
    g_ctx.jniHelperClz = (jclass)env->NewGlobalRef(clz);

    g_ctx.setSkipMode = env->GetStaticMethodID(
            g_ctx.jniHelperClz, "UpdateSkipMode", "(I)V");

    g_ctx.setAutomode = env->GetStaticMethodID(
            g_ctx.jniHelperClz, "UpdateAutomode", "(Z)V");

    g_ctx.setOnsPtr = env->GetStaticMethodID(
            g_ctx.jniHelperClz, "UpdateOnsPtr", "(J)V");

    g_ctx.done = 0;
    return JNI_VERSION_1_6;
}

void getEnv() {
    JNIEnv *env;

    if (g_ctx.javaVM->GetEnv((void **)&env, JNI_VERSION_1_6) != JNI_OK) {
        return;
    }
    g_ctx.env = env;
}

void JNI_SetSkipMode(int skip_mode) {
    getEnv();
    if (g_ctx.setSkipMode) {
        g_ctx.env->CallStaticVoidMethod(g_ctx.jniHelperClz, g_ctx.setSkipMode, skip_mode);
    }
}

void JNI_SetAutomode(bool automode) {
    getEnv();
    if (g_ctx.setAutomode) {
        g_ctx.env->CallStaticVoidMethod(g_ctx.jniHelperClz, g_ctx.setAutomode, automode);
    }
}

void JNI_SetOnsPtr(void* ptr) {
    getEnv();
    if (g_ctx.setOnsPtr) {
        g_ctx.env->CallStaticVoidMethod(g_ctx.jniHelperClz, g_ctx.setOnsPtr, (uintptr_t)ptr);
    }
}

#endif //__ANDROID__