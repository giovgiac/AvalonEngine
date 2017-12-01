/**
 * Timer.h
 *
 * Copyright (c) Giovanni Giacomo. All Rights Reserved.
 *
 */

#pragma once

#include <Core/Object.h>

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
		double SecsPerCount;
		double DeltaTime;
		uint64 BaseTime;
		uint64 CurrentTime;
		uint64 PausedTime;
		uint64 PreviousTime;
		uint64 StopTime;
		bool Stopped;

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
		inline float GetDeltaTime(void) const { return (float)DeltaTime; }
	};
}