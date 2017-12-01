/**
 * Timer.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "Timer.h"

#include <time.h>

namespace Avalon 
{
	ATimer::ATimer(void)
		: BaseTime(0), CurrentTime(0), DeltaTime(-1.0), PausedTime(0), PreviousTime(0), StopTime(0), Stopped(false)
	{
		uint64 CountsPerSec = CLOCKS_PER_SEC;

		// Calculate Period
		SecsPerCount = 1.0 / (double)CountsPerSec;
	}

	void ATimer::Reset(void) {
		// Get Current Time
		CurrentTime = clock();

		// Set Times
		BaseTime = CurrentTime;
		PreviousTime = CurrentTime;
		StopTime = 0;
		Stopped = false;
	}

	void ATimer::Start(void) {
		uint64 StartTime;

		// Get Current Time
		StartTime = clock();

		if (Stopped) {
			// Set Paused Time
			PausedTime += StartTime - StopTime;

			// Set Previous Time
			PreviousTime = StartTime;

			// Reset Stop Time and Stopped
			StopTime = 0;
			Stopped = false;
		}
	}

	void ATimer::Stop(void) {
		if (!Stopped) {
			// Get Current Time
			CurrentTime = clock();

			// Set Stop Time and Stopped
			StopTime = CurrentTime;
			Stopped = true;
		}
	}

	void ATimer::Tick(void) {
		if (Stopped) {
			DeltaTime = 0.0;
			return;
		}

		// Get Current Time
		CurrentTime = clock();

		// Compute Delta Time
		DeltaTime = (CurrentTime - PreviousTime) * SecsPerCount;

		// Set Previous Time
		PreviousTime = CurrentTime;

		// Ensure Non-Negative Delta Time
		if (DeltaTime < 0.0)
			DeltaTime = 0.0;
	}

	float ATimer::GetElapsedTime(void) const {
		if (Stopped)
			return (float)(((StopTime - PausedTime) - BaseTime) * SecsPerCount);
		else
			return (float)(((CurrentTime - PausedTime) - BaseTime) * SecsPerCount);
	}
}