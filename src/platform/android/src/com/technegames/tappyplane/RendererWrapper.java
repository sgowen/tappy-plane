package com.technegames.tappyplane;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView.Renderer;
import android.os.SystemClock;

import com.technegames.tappyplane.platform.PlatformFileUtils;

public final class RendererWrapper implements Renderer
{
	/*
	 * These definitions are copied directly from src/core/Assets.h
	 */
	private static final short ASCEND_SOUND = 1;
	private static final short SCORE_SOUND = 2;
	private static final short HIT_SOUND = 3;
	private static final short LAND_SOUND = 4;

	private static final Logger logger = new Logger(RendererWrapper.class);

	static
	{
		System.loadLibrary("game");
	}

	private final MainActivity activity;
	private final Audio audio;
	private final Sound ascendSound;
	private final Sound scoreSound;
	private final Sound hitSound;
	private final Sound landSound;
	private final int deviceScreenWidth;
	private final int deviceScreenHeight;
	private boolean isInitialized;

	public RendererWrapper(MainActivity activity, int deviceScreenWidth, int deviceScreenHeight)
	{
		this.activity = activity;
		this.audio = new Audio(activity.getAssets());
		this.ascendSound = audio.newSound("ascend.ogg");
		this.scoreSound = audio.newSound("score.ogg");
		this.hitSound = audio.newSound("hit.ogg");
		this.landSound = audio.newSound("land.ogg");
		this.deviceScreenWidth = deviceScreenWidth;
		this.deviceScreenHeight = deviceScreenHeight;
		this.isInitialized = false;
	}

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config)
	{
		logger.debug("GL Surface created!");

		if (!isInitialized)
		{
			PlatformFileUtils.init_asset_manager(activity.getAssets());
			init();
			isInitialized = true;
		}

		on_surface_created(deviceScreenWidth, deviceScreenHeight);
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height)
	{
		logger.debug("GL Surface changed!");

		on_surface_changed(width, height, width, height);
		on_resume();
	}

	// avoid GC in your threads. declare nonprimitive variables out of onDraw
	float smoothedDeltaRealTime_ms = 17.5f; // initial value, Optionally you can save the new computed value (will change with each hardware) in Preferences to optimize the first drawing frames
	float movAverageDeltaTime_ms = smoothedDeltaRealTime_ms; // mov Average start with default value
	long lastRealTimeMeasurement_ms; // temporal storage for last time measurement

	// smooth constant elements to play with
	static final float movAveragePeriod = 40; // #frames involved in average calc (suggested values 5-100)
	static final float smoothFactor = 0.1f; // adjusting ratio (suggested values 0.01-0.5)

	@Override
	public void onDrawFrame(GL10 gl)
	{
		int gameState = get_state();
		switch (gameState)
		{
			case 0:
				update(smoothedDeltaRealTime_ms / 1000);
				break;
			case 1:
				init();
				break;
			case 2:
				activity.finish();
				break;
			case 3:
				clear_state();
				handleFinalScore();
				break;
			case 4:
				clear_state();
				// TODO, show Leaderboards here if you want
				break;
			default:
				break;
		}

		present();
		handleSoundId(get_current_sound_id());

		// Moving average calc
		long currTimePick_ms = SystemClock.uptimeMillis();
		float realTimeElapsed_ms;
		if (lastRealTimeMeasurement_ms > 0)
		{
			realTimeElapsed_ms = (currTimePick_ms - lastRealTimeMeasurement_ms);
		}
		else
		{
			realTimeElapsed_ms = smoothedDeltaRealTime_ms; // just the first time
		}
		movAverageDeltaTime_ms = (realTimeElapsed_ms + movAverageDeltaTime_ms * (movAveragePeriod - 1)) / movAveragePeriod;

		// Calc a better aproximation for smooth stepTime
		smoothedDeltaRealTime_ms = smoothedDeltaRealTime_ms + (movAverageDeltaTime_ms - smoothedDeltaRealTime_ms) * smoothFactor;

		lastRealTimeMeasurement_ms = currTimePick_ms;
	}

	public void onResume()
	{
		on_resume();
	}

	public void onPause(final boolean isFinishing)
	{
		on_pause();
	}

	public void handleTouchDown(float rawX, float rawY)
	{
		on_touch_down(rawX, rawY);
	}

	public void handleTouchDragged(float rawX, float rawY)
	{
		on_touch_dragged(rawX, rawY);
	}

	public void handleTouchUp(float rawX, float rawY)
	{
		on_touch_up(rawX, rawY);
	}

	public boolean handleOnBackPressed()
	{
		return handle_on_back_pressed();
	}

	private void handleSoundId(short soundId)
	{
		switch (soundId)
		{
			case ASCEND_SOUND:
				ascendSound.play(1);
				break;
			case SCORE_SOUND:
				scoreSound.play(1);
				break;
			case HIT_SOUND:
				hitSound.play(1);
				break;
			case LAND_SOUND:
				landSound.play(1);
				break;
			default:
				break;
		}
	}

	private void handleFinalScore()
	{
		int score = get_score();
		int bestScore = AppPrefs.getInstance(activity).getBestScore();
		if (score > bestScore)
		{
			AppPrefs.getInstance(activity).setBestScore(score);
		}

		set_best_score(AppPrefs.getInstance(activity).getBestScore());
	}

	private static native void on_surface_created(int pixelWidth, int pixelHeight);

	private static native void on_surface_changed(int pixelWidth, int pixelHeight, int dpWidth, int dpHeight);

	private static native void init();

	private static native void on_resume();

	private static native void on_pause();

	private static native void update(float deltaTime);

	private static native void present();

	private static native void on_touch_down(float normalized_x, float normalized_y);

	private static native void on_touch_dragged(float normalized_x, float normalized_y);

	private static native void on_touch_up(float normalized_x, float normalized_y);

	private static native short get_current_sound_id();

	private static native int get_state();

	private static native void clear_state();

	private static native int get_score();

	private static native void set_best_score(int best_score);

	private static native boolean handle_on_back_pressed();
}