//
//  renderer_wrapper.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include <jni.h>
#include "game.h"
#include "macros.h"

/* These functions are called from Java. */
extern "C"
{
JNIEXPORT void JNICALL Java_com_technegames_tappyplane_RendererWrapper_on_1surface_1created(JNIEnv * env, jclass cls, jint pixel_width, jint pixel_height);
JNIEXPORT void JNICALL Java_com_technegames_tappyplane_RendererWrapper_on_1surface_1changed(JNIEnv * env, jclass cls, jint pixel_width, jint pixel_height, jint dp_width, jint dp_height);
JNIEXPORT void JNICALL Java_com_technegames_tappyplane_RendererWrapper_init(JNIEnv* env, jclass cls);
JNIEXPORT void JNICALL Java_com_technegames_tappyplane_RendererWrapper_on_1resume(JNIEnv* env, jclass cls);
JNIEXPORT void JNICALL Java_com_technegames_tappyplane_RendererWrapper_on_1pause(JNIEnv* env, jclass cls);
JNIEXPORT void JNICALL Java_com_technegames_tappyplane_RendererWrapper_update(JNIEnv* env, jclass cls, jfloat delta_time);
JNIEXPORT void JNICALL Java_com_technegames_tappyplane_RendererWrapper_present(JNIEnv* env, jclass cls);
JNIEXPORT void JNICALL Java_com_technegames_tappyplane_RendererWrapper_on_1touch_1down(JNIEnv* env, jclass cls, jfloat raw_touch_x, jfloat raw_touch_y);
JNIEXPORT void JNICALL Java_com_technegames_tappyplane_RendererWrapper_on_1touch_1dragged(JNIEnv* env, jclass cls, jfloat raw_touch_x, jfloat raw_touch_y);
JNIEXPORT void JNICALL Java_com_technegames_tappyplane_RendererWrapper_on_1touch_1up(JNIEnv* env, jclass cls, jfloat raw_touch_x, jfloat raw_touch_y);
JNIEXPORT short JNICALL Java_com_technegames_tappyplane_RendererWrapper_get_1current_1sound_1id(JNIEnv* env, jclass cls);
JNIEXPORT int JNICALL Java_com_technegames_tappyplane_RendererWrapper_get_1state(JNIEnv* env, jclass cls);
JNIEXPORT void JNICALL Java_com_technegames_tappyplane_RendererWrapper_clear_1state(JNIEnv* env, jclass cls);
JNIEXPORT int JNICALL Java_com_technegames_tappyplane_RendererWrapper_get_1score(JNIEnv* env, jclass cls);
JNIEXPORT void JNICALL Java_com_technegames_tappyplane_RendererWrapper_set_1best_1score(JNIEnv* env, jclass cls, jint best_score);
JNIEXPORT bool JNICALL Java_com_technegames_tappyplane_RendererWrapper_handle_1on_1back_1pressed(JNIEnv* env, jclass cls);
};

JNIEXPORT void JNICALL Java_com_technegames_tappyplane_RendererWrapper_on_1surface_1created(JNIEnv * env, jclass cls, jint pixel_width, jint pixel_height)
{
	UNUSED(env);
	UNUSED(cls);
	on_surface_created(pixel_width, pixel_height);
}

JNIEXPORT void JNICALL Java_com_technegames_tappyplane_RendererWrapper_on_1surface_1changed(JNIEnv * env, jclass cls, jint pixel_width, jint pixel_height, jint dp_width, jint dp_height)
{
	UNUSED(env);
	UNUSED(cls);
	on_surface_changed(pixel_width, pixel_height, dp_width, dp_height);
}

JNIEXPORT void JNICALL Java_com_technegames_tappyplane_RendererWrapper_init(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);
	init(false);
}

JNIEXPORT void JNICALL Java_com_technegames_tappyplane_RendererWrapper_on_1resume(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);
	on_resume();
}

JNIEXPORT void JNICALL Java_com_technegames_tappyplane_RendererWrapper_on_1pause(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);
	on_pause();
}

JNIEXPORT void JNICALL Java_com_technegames_tappyplane_RendererWrapper_update(JNIEnv* env, jclass cls, jfloat delta_time)
{
	UNUSED(env);
	UNUSED(cls);
	update(delta_time);
}

JNIEXPORT void JNICALL Java_com_technegames_tappyplane_RendererWrapper_present(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);
	present();
}

JNIEXPORT void JNICALL Java_com_technegames_tappyplane_RendererWrapper_on_1touch_1down(JNIEnv* env, jclass cls, jfloat raw_touch_x, jfloat raw_touch_y)
{
	UNUSED(env);
	UNUSED(cls);
	on_touch_down(raw_touch_x, raw_touch_y);
}

JNIEXPORT void JNICALL Java_com_technegames_tappyplane_RendererWrapper_on_1touch_1dragged(JNIEnv* env, jclass cls, jfloat raw_touch_x, jfloat raw_touch_y)
{
	UNUSED(env);
	UNUSED(cls);
	on_touch_dragged(raw_touch_x, raw_touch_y);
}

JNIEXPORT void JNICALL Java_com_technegames_tappyplane_RendererWrapper_on_1touch_1up(JNIEnv* env, jclass cls, jfloat raw_touch_x, jfloat raw_touch_y)
{
	UNUSED(env);
	UNUSED(cls);
	on_touch_up(raw_touch_x, raw_touch_y);
}

JNIEXPORT short JNICALL Java_com_technegames_tappyplane_RendererWrapper_get_1current_1sound_1id(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);
	return get_current_sound_id();
}

JNIEXPORT int JNICALL Java_com_technegames_tappyplane_RendererWrapper_get_1state(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);
	return get_state();
}

JNIEXPORT void JNICALL Java_com_technegames_tappyplane_RendererWrapper_clear_1state(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);
	clear_state();
}

JNIEXPORT int JNICALL Java_com_technegames_tappyplane_RendererWrapper_get_1score(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);
	return get_score();
}

JNIEXPORT void JNICALL Java_com_technegames_tappyplane_RendererWrapper_set_1best_1score(JNIEnv* env, jclass cls, jint best_score)
{
	UNUSED(env);
	UNUSED(cls);
	set_best_score(best_score);
}

JNIEXPORT bool JNICALL Java_com_technegames_tappyplane_RendererWrapper_handle_1on_1back_1pressed(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);
	return handle_on_back_pressed();
}
