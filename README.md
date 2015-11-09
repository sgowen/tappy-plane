Tappy Plane
===========

<img src="http://gowengamedev.com/wp-content/uploads/2014/02/Feature1.png" />

A lightweight cross-platform Flappy Bird clone for Android, iOS, Windows Phone 8, and Nintendo 3DS!

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

1. Download the Android NDK from https://developer.android.com/ndk/downloads/index.html if you do not already have it
2. Open app/src/main/jni/Android.mk and edit the first line (starting with NDKROOT :=) to point to your Android NDK installation root directory
3. Open in Android Studio (src/platform/android)
4. Open the local.properties file and add the following line: ndk.dir=**path to ndk, same as in Android.mk**
5. Run it!

## Setup Instructions for iOS

After you implement the fix for libpng described above, all you need to do is open the project in Xcode and run it!

## Setup Instructions for Windows Phone 8

Assuming you already have the Windows Phone 8 sdk installed, just open the project in Visual Studio and run it!

## Setup Instructions for Nintendo 3DS

1. I recommend installing the Homebrew Launcher first (it launches 3dsx files for you, which is nice). You can learn how to do this here: http://smealum.github.io/3ds/
2. Install NetBeans with C/C++ support.
3. Follow the tutorial here on how to set up your NetBeans development environment: http://www.3dbrew.org/wiki/Setting_up_Development_Environment, but ignore the part at the bottom (Building homebrew for distribution) if you just plan on accessing your build via the Homebrew Launcher
4. Download my fork of sf2dlib from https://github.com/GowenGameDevOpenSource/sf2dlib
5. At the top of the sf2dlib Makefile, add a declaration for AEMSTRO (after DEVKITPRO and DEVKITARM): export AEMSTRO=<Path to aemstro containing the python scripts>
6. Build sf2dlib
7. Back in tappy-plane, add the following line to the top of your Makefile (again after DEVKITPRO and DEVKITARM): export LIBSF2D=<Path to sf2dlib containing the lib and include directories>
8. Build!