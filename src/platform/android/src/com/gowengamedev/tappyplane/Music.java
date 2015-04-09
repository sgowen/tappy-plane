package com.gowengamedev.tappyplane;

import android.content.res.AssetFileDescriptor;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;

public final class Music implements OnCompletionListener
{
    private final MediaPlayer mediaPlayer;

    private boolean isPrepared;

    public Music(AssetFileDescriptor assetDescriptor)
    {
        this.mediaPlayer = new MediaPlayer();

        try
        {
            mediaPlayer.setDataSource(assetDescriptor.getFileDescriptor(), assetDescriptor.getStartOffset(), assetDescriptor.getLength());
            mediaPlayer.prepare();
            isPrepared = true;
            mediaPlayer.setOnCompletionListener(this);
        }
        catch (Exception exception)
        {
            throw new RuntimeException("Exception occurred while trying to load music: " + exception.getMessage());
        }
    }

    public void onCompletion(MediaPlayer mediaPlayer)
    {
        synchronized (this)
        {
            isPrepared = false;
        }
    }

    public Exception play()
    {
        if (isPlaying())
        {
            return null;
        }

        try
        {
            synchronized (this)
            {
                if (!isPrepared)
                {
                    mediaPlayer.prepare();
                }

                mediaPlayer.start();
                return null;
            }
        }
        catch (Exception e)
        {
            isPrepared = false;
            return e;
        }
    }

    public void stop()
    {
        mediaPlayer.stop();

        synchronized (this)
        {
            isPrepared = false;
        }
    }

    public void pause()
    {
        if (isPlaying())
        {
            mediaPlayer.pause();
        }
    }

    public void setLooping(boolean isLooping)
    {
        mediaPlayer.setLooping(isLooping);
    }

    public void setVolume(float volume)
    {
        mediaPlayer.setVolume(volume, volume);
    }

    public boolean isPlaying()
    {
        return mediaPlayer.isPlaying();
    }

    public boolean isStopped()
    {
        return !isPrepared;
    }

    public boolean isLooping()
    {
        return mediaPlayer.isLooping();
    }

    public void dispose()
    {
        if (mediaPlayer == null)
        {
            return;
        }

        if (mediaPlayer.isPlaying())
        {
            mediaPlayer.stop();
        }

        mediaPlayer.release();
    }
}