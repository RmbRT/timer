/** @file Timer.hpp
	Contains the timer utility class.

	Copyright (C) 2019  RmbRT <steffen.rattay@gmail.com>
	
	This file is part of timer.

	timer is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

	timer is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.

	You should have received a copy of the GNU Affero General Public License along with timer.  If not, see <http://www.gnu.org/licenses/>. */
#ifndef __timer_timer_hpp_defined
#define __timer_timer_hpp_defined

#include <chrono>

namespace timer
{
	template<
		class Time = std::chrono::seconds,
		class Duration = double,
		class Clock = std::conditional<
			std::chrono::high_resolution_clock::is_steady,
			std::chrono::high_resolution_clock,
			std::chrono::steady_clock>::type>
	/** Time interval measurement class.
		Has an internal accumulator. `start()` starts recording time. `stop()` pauses the timer, and adds the elapsed time to the accumulator. Only the accumulator is looked at when retrieving time. `zero()` resets the accumulator. */
	class Timer
	{
		/** The accumulated time. */
		std::chrono::duration<Duration, typename Time::period> m_accumulated;
		/** The moment the timer started recording. */
		std::chrono::time_point<Clock> m_start;
		/** The moment the timer stopped recording. */
		std::chrono::time_point<Clock> m_stop;
	public:
		static_assert(Clock::is_steady, "The chosen clock type is not steady.");

		/** The timer's duration accuracy type. */
		typedef Duration duration_t;

		/** Creates a paused timer with no accumulated time. */
		Timer();

		/** Starts recording time. */
		void start();
		/** Stops recording time, and adds the elapsed time to the internal accumulator.
		@return
			The accumulated recorded elapsed time. */
		Duration stop();

		/** Resets the internal accumulated time to 0 (without starting/stopping the timer). */
		void zero();

		/** Retrieves the overall recorded time.
			Only the time recorded until the last call to `stop()` is returned.
		@return
			The accumulated recorded elapsed time. */
		inline Duration elapsed() const;

		template<class Callable, class ...Args>
		/** Measures the latency of a function call.
		@param[in] c:
			The callable to measure.
		@param[in] args:
			The arguments to pass to c.
		@return
			The elapsed time in seconds. */
		static Duration latency(
			Callable c,
			Args&& ...args);
	};

	template<class Callable, class ...Args>
	/** Measures the latency of a function call using the default timer.
		@param[in] c:
			The callable to measure.
		@param[in] args:
			The arguments to pass to c.
		@return
			The elapsed time in seconds. */
	inline typename Timer<>::duration_t latency(
		Callable c,
		Args&& ...args);
}

#include "Timer.inl"

#endif