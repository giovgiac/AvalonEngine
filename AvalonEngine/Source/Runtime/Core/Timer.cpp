/**
 * Timer.cpp
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#include "Timer.h"

namespace Avalon
{
	ATimer::ATimer(void)
		:
		BaseTime(std::chrono::high_resolution_clock::time_point(std::chrono::high_resolution_clock::duration::zero())),
		CurrentTime(std::chrono::high_resolution_clock::time_point(std::chrono::high_resolution_clock::duration::zero())),
		PausedTime(std::chrono::high_resolution_clock::time_point(std::chrono::high_resolution_clock::duration::zero())),
		PreviousTime(std::chrono::high_resolution_clock::time_point(std::chrono::high_resolution_clock::duration::zero())),
		StopTime(std::chrono::high_resolution_clock::time_point(std::chrono::high_resolution_clock::duration::zero())),
		DeltaTime(-1.0),
		bStopped(false)
	{

	}

	void ATimer::Reset(void) {
		// Get Current Time
		CurrentTime = std::chrono::high_resolution_clock::now();
		
		// Set Times
		BaseTime = CurrentTime;
		PreviousTime = CurrentTime;
		StopTime = std::chrono::high_resolution_clock::time_point(std::chrono::high_resolution_clock::duration::zero());
		bStopped = false;
	}

	void ATimer::Start(void) {
		std::chrono::time_point<std::chrono::high_resolution_clock> StartTime;

		// Get Current Time
		StartTime = std::chrono::high_resolution_clock::now();

		if (bStopped) {
			// Set Paused Time
			PausedTime += StartTime - StopTime;

			// Set Previous Time
			PreviousTime = StartTime;

			// Reset Stop Time and bStopped
			StopTime = std::chrono::high_resolution_clock::time_point(std::chrono::high_resolution_clock::duration::zero());
			bStopped = false;
		}
	}

	void ATimer::Stop(void) {
		if (!bStopped) {
			// Get Current Time
			CurrentTime = std::chrono::high_resolution_clock::now();

			// Set Stop Time and bStopped
			StopTime = CurrentTime;
			bStopped = true;
		}
	}

	void ATimer::Tick(void) {
		if (bStopped) {
			DeltaTime = 0.0;
			return;
		}

		// Get Current Time
		CurrentTime = std::chrono::high_resolution_clock::now();

		// Compute Delta Time
		DeltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(CurrentTime - PreviousTime).count() / 10e8;

		// Set Previous Time
		PreviousTime = CurrentTime;

		// Ensure Non-Negative Delta Time
		if (DeltaTime < 0.0)
			DeltaTime = 0.0;
	}

	float ATimer::GetDeltaTime(void) const
	{
		return (float)DeltaTime;
	}

	float ATimer::GetElapsedTime(void) const {
		if (bStopped)
			return (float)(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::time_point(StopTime - PausedTime) - BaseTime).count() / 10e8);
		else
			return (float)(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::time_point(CurrentTime - PausedTime) - BaseTime).count() / 10e8);
	}
}