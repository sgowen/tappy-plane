package com.technegames.tappyplane;

import android.media.SoundPool;

public final class Sound
{
	private final SoundPool soundPool;
	private final int soundID;

	private int streamID;

	public Sound(SoundPool soundPool, int soundID)
	{
		this.soundPool = soundPool;
		this.soundID = soundID;
	}

	public void play(float volume)
	{
		this.streamID = soundPool.play(soundID, volume, volume, 0, 0, 1);
	}

	public void pause()
	{
		soundPool.pause(streamID);
	}

	public void resume()
	{
		soundPool.resume(streamID);
	}

	public void stop()
	{
		soundPool.stop(streamID);
	}

	public void dispose()
	{
		soundPool.unload(soundID);
	}
}