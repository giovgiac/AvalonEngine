/**
 * Timer.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Core/Object.h>

#include <chrono>

namespace Avalon 
{
	/**
	 * ATimer Class
	 *
	 * This class is responsible for keeping time in any operating system that supports
	 * the C standard library.
	 *
	 */
	class ATimer : public AObject
	{
	private:
		bool bStopped;
		double DeltaTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> BaseTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> CurrentTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> PausedTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> PreviousTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> StopTime;

	public:
		/**
		 * ATimer Constructor
		 *
		 * This constructor initializes the times to their default values
		 * and calculates the period and frequency of the timer.
		 *
		 */
		ATimer(void);

		/**
		 * ATimer Reset
		 *
		 * This method resets the timer, resetting it's baseTime to curTime.
		 *
		 */
		void Reset(void);

		/**
		 * ATimer Start
		 *
		 * This method starts the timer, if it was previously stopped, counting
		 * time normally, instead of to pausedTime.
		 *
		 */
		void Start(void);

		/**
		 * ATimer Stop
		 *
		 * This method stops the timer, adding future time differences to the 
		 * pausedTime.
		 *
		 */
		void Stop(void);

		/**
		 * ATimer Tick
		 *
		 * This method is supposed to be called every frame and is responsible
		 * for calculating the deltaTime between frames.
		 *
		 */
		void Tick(void);

		/**
		 * ATimer GetElapsedTime
		 *
		 * This method calculates the total elapsed time, since the start of the
		 * application or the last timer reset.
		 *
		 * @return float: A float with the total time elapsed in seconds.
		 *
		 */
		float GetElapsedTime(void) const;

		/**
		 * ATimer GetDeltaTime
		 *
		 * This method is a getter for the deltaTime between the current and 
		 * previous frames.
		 *
		 * @return float: A float with the delta time in seconds.
		 *
		 */
		float GetDeltaTime(void) const;
	};
}