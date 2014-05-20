Tappy Plane
===========

A lightweight cross-platform Flappy Bird clone for Android, iOS, and Windows Phone 8.
In this game, you tap to control a colorful plane through a cave!
This project serves as an excellent template for those wanting to develop cross-platform games for mobile without relying on cross-platform frameworks. It uses precompiler directives to intuitively switch between OpenGL ES and Direct3D rendering. Roughly 90% of the game is written in C++. The other 10% of the game is a reusable wrapper layer written in Java for Android, Objective-C for iOS, and C# for Windows Phone 8.

## Setup Instructions for Android/iOS

1. Download version 1.6.8 of the libpng library from http://sourceforge.net/projects/libpng/files/libpng16/older-releases/1.6.8/
2. Extract the contents of lpng168.zip into the 3rdparty/libpng folder.
3. Move scripts/pnglibconf.h.prebuilt into the root folder and rename it to pnglibconf.h
4. Replace lines 123-127 of pngpriv.h with **#define PNG_ARM_NEON_OPT 0**

## Setup Instructions for Android

1. Download the Android NDK from https://developer.android.com/tools/sdk/ndk/index.html if you do not already have it
2. Open src/platform/android/jni/Android.mk
3. Edit the first line (starting with NDKROOT :=) to point to your Android NDK installation root folder

## Setup Instructions for Windows Phone 8

1. Download the July 1st, 2013 release of the DirectXTK library from https://directxtk.codeplex.com/releases/view/108806
2. Extract its contents to the 3rdparty\DirectXTK folder
