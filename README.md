Tappy Plane
===========

<img src="http://gowengamedev.com/wp-content/uploads/2014/02/Feature1.png" />

A lightweight cross-platform Flappy Bird clone for Android, iOS, and Windows Phone 8.

In this game, you tap to control a colorful plane through a cave!

This project serves as an excellent template for those wanting to develop cross-platform games for mobile without relying on cross-platform frameworks. It uses precompiler directives to intuitively switch between OpenGL ES and Direct3D rendering. Roughly 90% of the game is written in C++. The other 10% of the game is a reusable wrapper layer written in Java for Android, Objective-C for iOS, and C# for Windows Phone 8.

<img src="http://gowengamedev.com/github/tappy_plane_showcase.png" />

## Graphics

Thanks goes to <a href="http://kenney.nl/" target="_blank">Kenney</a> for this awesome set of free graphics!

## Setup Instructions for Android/iOS

1. Download version **1.6.8** of the libpng library from http://sourceforge.net/projects/libpng/files/libpng16/older-releases/1.6.8/
2. Extract the contents of lpng168.zip into the 3rdparty/libpng directory.
3. Move scripts/pnglibconf.h.prebuilt into the root directory and rename it to pnglibconf.h
4. Replace lines 123-127 of pngpriv.h with **#define PNG_ARM_NEON_OPT 0**

## Setup Instructions for Android

1. Download the Android NDK from https://developer.android.com/tools/sdk/ndk/index.html if you do not already have it
2. Open src/platform/android/jni/Android.mk
3. Edit the first line (starting with NDKROOT :=) to point to your Android NDK installation root directory
4. Open ADT Eclipse > right-click your workspace > Import... > Existing Projects into Workspace > Browse... > tappy-plane > Finish
5. The tappy-plane Eclipse project is bundled with an NDK builder, but for it to work, you will need to point it to where your **ndk-build** is installed. Right-click the tappy-plane project > Properties > Builders > Tappy Plane NDK Builder > Edit... > Location: > set the path to your **ndk-build** here. It is located in the root of your Android NDK installation directory.
6. Navigate to the assets directory and run the following commands (necessary for linking the OGL shaders):
ln -s ../../../core/framework/opengles/texture_shader.vsh texture_shader.vsh
ln -s ../../../core/framework/opengles/texture_shader.fsh texture_shader.fsh
ln -s ../../../core/framework/opengles/color_shader.vsh color_shader.vsh
ln -s ../../../core/framework/opengles/color_shader.fsh color_shader.fsh

## Setup Instructions for Windows Phone 8

Assuming you already have the Windows Phone 8 sdk installed, just open the project in Visual Studio and run it!