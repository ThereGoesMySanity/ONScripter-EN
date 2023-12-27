#ifdef __ANDROID__

#include "jniUtils.h"
#include <string.h>
#include <SDL.h>
typedef struct tick_context {
    JavaVM *javaVM;
    JNIEnv *env;
    jclass jniHelperClz;
    jclass activityClz;
    jmethodID setSkipMode;
    jmethodID setAutomode;
    jmethodID setOnsPtr;
    jmethodID setWindowTitle;
    int done;
} TickContext;
TickContext g_ctx = {0};

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;

    g_ctx.javaVM = vm;
    if (vm->GetEnv((void **)&env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;  // JNI version not supported.
    }

    jclass clz = env->FindClass("com/tgms/onscripter/JniState");
    g_ctx.jniHelperClz = (jclass)env->NewGlobalRef(clz);

    g_ctx.setSkipMode = env->GetStaticMethodID(
            g_ctx.jniHelperClz, "UpdateSkipMode", "(I)V");

    g_ctx.setAutomode = env->GetStaticMethodID(
            g_ctx.jniHelperClz, "UpdateAutomode", "(Z)V");

    g_ctx.setOnsPtr = env->GetStaticMethodID(
            g_ctx.jniHelperClz, "UpdateOnsPtr", "(J)V");

    clz = env->FindClass("org/libsdl/app/SDLActivity");
    g_ctx.activityClz = (jclass)env->NewGlobalRef(clz);

    g_ctx.setWindowTitle = env->GetStaticMethodID(
            g_ctx.activityClz,"setActivityTitle", "(Ljava/lang/String;)Z");

    g_ctx.done = 0;
    return JNI_VERSION_1_6;
}

void getEnv() {
    g_ctx.env = (JNIEnv*)SDL_AndroidGetJNIEnv();
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

void JNI_SetWindowTitle(const char* title) {
    getEnv();
    JNIEnv *env = g_ctx.env;
    if (g_ctx.setWindowTitle) {
        jobject bb = env->NewDirectByteBuffer((void*)title, strlen(title));

        jclass cls_Charset = env->FindClass("java/nio/charset/Charset");
        jmethodID mid_Charset_forName = env->GetStaticMethodID(cls_Charset, "forName", "(Ljava/lang/String;)Ljava/nio/charset/Charset;");
        jobject charset = env->CallStaticObjectMethod(cls_Charset, mid_Charset_forName, env->NewStringUTF("UTF-8"));

        jmethodID mid_Charset_decode = env->GetMethodID(cls_Charset, "decode", "(Ljava/nio/ByteBuffer;)Ljava/nio/CharBuffer;");
        jobject cb = env->CallObjectMethod(charset, mid_Charset_decode, bb);
        env->DeleteLocalRef(bb);

        jclass cls_CharBuffer = env->FindClass("java/nio/CharBuffer");
        jmethodID mid_CharBuffer_toString = env->GetMethodID(cls_CharBuffer, "toString", "()Ljava/lang/String;");
        jstring jtitle = (jstring)env->CallObjectMethod(cb, mid_CharBuffer_toString);
        env->CallStaticBooleanMethod(g_ctx.activityClz, g_ctx.setWindowTitle, jtitle);
        env->DeleteLocalRef(jtitle);
    }
}

#endif //__ANDROID__