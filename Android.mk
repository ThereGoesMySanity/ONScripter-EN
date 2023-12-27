LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := extlib/SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
    $(LOCAL_PATH)/$(SDL_PATH)_mixer/include \
    $(LOCAL_PATH)/$(SDL_PATH)_image/include \
    $(LOCAL_PATH)/$(SDL_PATH)_ttf/include \
    $(LOCAL_PATH)/extlib/smpeg/smpeg.h \
    $(LOCAL_PATH)/extlib/bzip2-1.0.8 \
    $(LOCAL_PATH)/extlib/vorbis/include
    $(LOCAL_PATH)/extlib/lua-5.4.6/src/
# Add your application source files here...
LOCAL_SRC_FILES := $(wildcard $(LOCAL_PATH)/*.cpp) \
        $(wildcard $(LOCAL_PATH)/extlib/bzip2-1.0.8/*.c)
        $(wildcard $(LOCAL_PATH)/extlib/lua-5.4.6/src/*.c)

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_mixer SDL2_image SDL2_ttf smpeg2 vorbis

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -lOpenSLES -llog -landroid

LOCAL_CFLAGS := -DUSE_OGG_VORBIS

include $(BUILD_SHARED_LIBRARY)
