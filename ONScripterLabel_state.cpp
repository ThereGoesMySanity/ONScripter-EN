#include "ONScripterLabel.h"
#include <SDL.h>
#ifdef __ANDROID__
#include "jniUtils.h"
#endif

#define ONS_BREAK_EVENT    (SDL_USEREVENT+6)

#define CAN_INPUT ((event_mode & (WAIT_INPUT_MODE | WAIT_TEXTBTN_MODE)) && \
                !key_pressed_flag && !automode_flag && !ctrl_pressed_status)

inline void pushBreak() {
    SDL_Event event;
    event.type = ONS_BREAK_EVENT;
    SDL_PushEvent(&event);
}

void ONScripterLabel::SetSkipMode(int newValue) {
#ifdef __ANDROID__
    if (newValue != skip_mode) JNI_SetSkipMode(newValue);
#endif
    skip_mode = newValue;
}
void ONScripterLabel::SetAutomode(bool newValue) {
#ifdef __ANDROID__
    if (automode_flag != newValue) JNI_SetAutomode(newValue);
#endif
    automode_flag = newValue;
}
void ONScripterLabel::TrySetNormalSkip(bool newValue) {
    if (newValue && !(skip_mode & SKIP_NORMAL) && CAN_INPUT) {
        skip_effect = true; // short-circuit a current effect
        SetSkipMode(skip_mode | SKIP_NORMAL);
        key_pressed_flag = true;
        current_button_state.set(0);
        volatile_button_state.set(0);
        stopCursorAnimation(clickstr_state);
        pushBreak();
    } else if (!newValue) {
        SetSkipMode(skip_mode & ~SKIP_NORMAL);
    }
}
void ONScripterLabel::TrySetEopSkip(bool newValue) {
    if (CAN_INPUT) {
        if (newValue && !(skip_mode & SKIP_TO_EOP)) {
            SetSkipMode(skip_mode | SKIP_TO_EOP);
            current_button_state.set(0);
            volatile_button_state.set(0);
            stopCursorAnimation( clickstr_state );
            pushBreak();
        } else if (!newValue && (skip_mode & SKIP_TO_EOP)) {
            SetSkipMode(skip_mode & ~SKIP_TO_EOP);
        }
    }
}

void ONScripterLabel::TrySetAutomode(bool newValue) {
    if (newValue && !ctrl_pressed_status && mode_ext_flag && !automode_flag && CAN_INPUT){
        SetAutomode(true);
        SetSkipMode(skip_mode & ~SKIP_NORMAL);
        key_pressed_flag = true;
        current_button_state.set(0);
        volatile_button_state.set(0);
        stopCursorAnimation( clickstr_state );
        pushBreak();
    } else if (!newValue) {
        SetAutomode(false);
    }
}