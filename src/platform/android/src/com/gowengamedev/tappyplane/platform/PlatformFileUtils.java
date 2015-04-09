package com.gowengamedev.tappyplane.platform;

import android.content.res.AssetManager;

public final class PlatformFileUtils
{
    public static native void init_asset_manager(AssetManager assetManager);
}