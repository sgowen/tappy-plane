package com.technegames.tappyplane;

import java.util.Map;
import java.util.Set;

import android.content.Context;
import android.content.SharedPreferences;

public final class AppPrefs implements SharedPreferences
{
	public static AppPrefs getInstance(Context context)
	{
		if (instance == null)
		{
			instance = new AppPrefs(context);
		}

		return instance;
	}

	private static final String SHARED_PREFERENCES_NAME = "Techne_Games_Preferences";
	private static final String BEST_SCORE = "BEST_SCORE";

	private static AppPrefs instance;

	private final SharedPreferences sharedPreferences;

	private AppPrefs(Context context)
	{
		this.sharedPreferences = context.getSharedPreferences(SHARED_PREFERENCES_NAME, Context.MODE_PRIVATE);
	}

	@Override
	public String getString(String key, String defValue)
	{
		return sharedPreferences.getString(key, defValue);
	}

	@Override
	public float getFloat(String key, float defValue)
	{
		return sharedPreferences.getFloat(key, defValue);
	}

	@Override
	public long getLong(String key, long defValue)
	{
		return sharedPreferences.getLong(key, defValue);
	}

	@Override
	public int getInt(String key, int defValue)
	{
		return sharedPreferences.getInt(key, defValue);
	}

	@Override
	public boolean getBoolean(String key, boolean defValue)
	{
		return sharedPreferences.getBoolean(key, defValue);
	}

	@Override
	public boolean contains(String key)
	{
		return sharedPreferences.contains(key);
	}

	@Override
	public Map<String, ?> getAll()
	{
		return sharedPreferences.getAll();
	}

	@Override
	public Editor edit()
	{
		return sharedPreferences.edit();
	}

	@Override
	public void registerOnSharedPreferenceChangeListener(OnSharedPreferenceChangeListener listener)
	{
		sharedPreferences.registerOnSharedPreferenceChangeListener(listener);
	}

	@Override
	public void unregisterOnSharedPreferenceChangeListener(OnSharedPreferenceChangeListener listener)
	{
		sharedPreferences.unregisterOnSharedPreferenceChangeListener(listener);
	}

	@Override
	public Set<String> getStringSet(String key, Set<String> defValues)
	{
		return null;
	}

	public int getBestScore()
	{
		return getInt(BEST_SCORE, 0);
	}

	public void setBestScore(int bestScore)
	{
		set(BEST_SCORE, bestScore);
	}

	public boolean clearAll()
	{
		return edit().clear().commit();
	}

	public boolean set(String key, String value)
	{
		if (value == null)
		{
			return edit().remove(key).commit();
		}

		return edit().putString(key, value).commit();
	}

	public boolean set(String key, float value)
	{
		return edit().putFloat(key, value).commit();
	}

	public boolean set(String key, long value)
	{
		return edit().putLong(key, value).commit();
	}

	public boolean set(String key, int value)
	{
		return edit().putInt(key, value).commit();
	}

	public boolean set(String key, boolean value)
	{
		return edit().putBoolean(key, value).commit();
	}
}