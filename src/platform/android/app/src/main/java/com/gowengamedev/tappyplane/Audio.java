package com.gowengamedev.tappyplane;

import java.io.IOException;

import android.content.res.AssetFileDescriptor;
import android.content.res.AssetManager;
import android.media.AudioManager;
import android.media.SoundPool;

public final class Audio
{
    private final AssetManager assets;
    private SoundPool soundPool;

    public Audio(AssetManager assets)
    {
        this.assets = assets;
        this.soundPool = new SoundPool(8, AudioManager.STREAM_MUSIC, 0);
    }

    public Music newMusic(String filename)
    {
        try
        {
            AssetFileDescriptor assetDescriptor = assets.openFd(filename);

            return new Music(assetDescriptor);
        }
        catch (IOException ioException)
        {
            throw new RuntimeException("Couldn't load music '" + filename + "'" + ioException.getMessage());
        }
    }

    public Sound newSound(String filename)
    {
        try
        {
            AssetFileDescriptor assetDescriptor = assets.openFd(filename);
            int soundID = soundPool.load(assetDescriptor, 1);

            return new Sound(soundPool, soundID);
        }
        catch (IOException ioException)
        {
            throw new RuntimeException("Couldn't load sound '" + filename + "'" + ioException.getMessage());
        }
    }

    public void reset()
    {
        this.soundPool.release();
        this.soundPool = null;
        this.soundPool = new SoundPool(8, AudioManager.STREAM_MUSIC, 0);
    }
}