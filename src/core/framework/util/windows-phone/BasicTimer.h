//
//  BasicTimer.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/25/14.
//  Copyright (c) 2014 Gowen Game Dev. All rights reserved.
//

#pragma once

#include <wrl.h>

// Helper class for basic timing.
ref class BasicTimer sealed
{
public:
	// Initializes internal timer values.
	BasicTimer()
	{
		Reset();
	}

	long long milliseconds_now()
	{
		static LARGE_INTEGER s_frequency;
		static BOOL s_use_qpc = QueryPerformanceFrequency(&s_frequency);
		if (s_use_qpc)
		{
			LARGE_INTEGER now;
			QueryPerformanceCounter(&now);
			return (1000LL * now.QuadPart) / s_frequency.QuadPart;
		}
		else
		{
			throw ref new Platform::FailureException();
		}
	}

	// Reset the timer to initial values.
	void Reset()
	{
		Update();

		smoothedDeltaRealTime_ms = 17.5f; // initial value, Optionally you can save the new computed value (will change with each hardware) in Preferences to optimize the first drawing frames
		movAverageDeltaTime_ms = smoothedDeltaRealTime_ms; // mov Average start with default value
	}

	// Update the timer's internal values.
	void Update()
	{
		// smooth constant elements to play with
		static float movAveragePeriod = 40; // #frames involved in average calc (suggested values 5-100)
		static float smoothFactor = 0.1f; // adjusting ratio (suggested values 0.01-0.5)

		// Moving average calc
		long currTimePick_ms = milliseconds_now();
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

	// Duration in seconds between the previous two calls to Update().
	property float Delta
	{
		float get() { return smoothedDeltaRealTime_ms / 1000; }
	}

private:
	float smoothedDeltaRealTime_ms;
	float movAverageDeltaTime_ms;
	long lastRealTimeMeasurement_ms; // temporal storage for last time measurement
};