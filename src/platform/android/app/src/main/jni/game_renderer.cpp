//
//  game_renderer.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include <jni.h>
#include "macros.h"
#include "AndroidOpenGLESGameScreen.h"

AndroidOpenGLESGameScreen *gameScreen;

/* These functions are called from Java. */
extern "C"
{
JNIEXPORT void JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_on_1surface_1created(JNIEnv * env, jclass cls, jint pixel_width, jint pixel_height);
JNIEXPORT void JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_on_1surface_1changed(JNIEnv * env, jclass cls, jint pixel_width, jint pixel_height, jint dp_width, jint dp_height);
JNIEXPORT void JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_init(JNIEnv* env, jclass cls);
JNIEXPORT void JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_on_1resume(JNIEnv* env, jclass cls);
JNIEXPORT void JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_on_1pause(JNIEnv* env, jclass cls);
JNIEXPORT void JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_update(JNIEnv* env, jclass cls, jfloat delta_time);
JNIEXPORT void JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_render(JNIEnv* env, jclass cls);
JNIEXPORT void JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_on_1touch_1down(JNIEnv* env, jclass cls, jfloat raw_touch_x, jfloat raw_touch_y);
JNIEXPORT void JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_on_1touch_1dragged(JNIEnv* env, jclass cls, jfloat raw_touch_x, jfloat raw_touch_y);
JNIEXPORT void JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_on_1touch_1up(JNIEnv* env, jclass cls, jfloat raw_touch_x, jfloat raw_touch_y);
JNIEXPORT short JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_get_1current_1sound_1id(JNIEnv* env, jclass cls);
JNIEXPORT int JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_get_1state(JNIEnv* env, jclass cls);
JNIEXPORT void JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_clear_1state(JNIEnv* env, jclass cls);
JNIEXPORT int JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_get_1score(JNIEnv* env, jclass cls);
JNIEXPORT void JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_set_1best_1score(JNIEnv* env, jclass cls, jint best_score);
JNIEXPORT bool JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_handle_1on_1back_1pressed(JNIEnv* env, jclass cls);
};

JNIEXPORT void JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_on_1surface_1created(JNIEnv * env, jclass cls, jint pixel_width, jint pixel_height)
{
	UNUSED(env);
	UNUSED(cls);

	gameScreen->onSurfaceCreated(pixel_width, pixel_height);
}

JNIEXPORT void JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_on_1surface_1changed(JNIEnv * env, jclass cls, jint pixel_width, jint pixel_height, jint dp_width, jint dp_height)
{
	UNUSED(env);
	UNUSED(cls);

	gameScreen->onSurfaceChanged(pixel_width, pixel_height);
}

JNIEXPORT void JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_init(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);

	gameScreen = new AndroidOpenGLESGameScreen();
}

JNIEXPORT void JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_on_1resume(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);

	gameScreen->onResume();
}

JNIEXPORT void JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_on_1pause(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);

	gameScreen->onPause();
}

JNIEXPORT void JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_update(JNIEnv* env, jclass cls, jfloat delta_time)
{
	UNUSED(env);
	UNUSED(cls);

	gameScreen->update(delta_time);
}

JNIEXPORT void JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_render(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);

	gameScreen->render();
}

JNIEXPORT void JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_on_1touch_1down(JNIEnv* env, jclass cls, jfloat raw_touch_x, jfloat raw_touch_y)
{
	UNUSED(env);
	UNUSED(cls);

	gameScreen->onTouch(DOWN, raw_touch_x, raw_touch_y);
}

JNIEXPORT void JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_on_1touch_1dragged(JNIEnv* env, jclass cls, jfloat raw_touch_x, jfloat raw_touch_y)
{
	UNUSED(env);
	UNUSED(cls);

	gameScreen->onTouch(DRAGGED, raw_touch_x, raw_touch_y);
}

JNIEXPORT void JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_on_1touch_1up(JNIEnv* env, jclass cls, jfloat raw_touch_x, jfloat raw_touch_y)
{
	UNUSED(env);
	UNUSED(cls);

	gameScreen->onTouch(UP, raw_touch_x, raw_touch_y);
}

JNIEXPORT short JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_get_1current_1sound_1id(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);

	return gameScreen->getCurrentSoundId();
}

JNIEXPORT int JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_get_1state(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);

	return gameScreen->getState();
}

JNIEXPORT void JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_clear_1state(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);

	gameScreen->clearState();
}

JNIEXPORT int JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_get_1score(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);

	return gameScreen->getScore();
}

JNIEXPORT void JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_set_1best_1score(JNIEnv* env, jclass cls, jint best_score)
{
	UNUSED(env);
	UNUSED(cls);

	gameScreen->setBestScore(best_score);
}

JNIEXPORT bool JNICALL Java_com_gowengamedev_tappyplane_GameRenderer_handle_1on_1back_1pressed(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);

	return gameScreen->handleOnBackPressed();
}
