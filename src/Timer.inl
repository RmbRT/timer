/*	Copyright (C) 2019  RmbRT <steffen.rattay@gmail.com>
	
	This file is part of timer.

	timer is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

	timer is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.

	You should have received a copy of the GNU Affero General Public License along with timer.  If not, see <http://www.gnu.org/licenses/>. */
#include <utility>

namespace timer
{
	template<class Time, class Duration, class Clock>
	Timer<Time, Duration, Clock>::Timer():
		m_accumulated(std::chrono::duration<Duration, typename Time::period>::zero()),
		m_start(),
		m_stop()
	{
	}

	template<class Time, class Duration, class Clock>
	void Timer<Time, Duration, Clock>::start()
	{
		m_start = m_stop = Clock::now();
	}

	template<class Time, class Duration, class Clock>
	Duration Timer<Time, Duration, Clock>::stop()
	{
		m_stop = Clock::now();
		m_accumulated += std::chrono::duration<Duration, typename Time::period>{m_stop - m_start};

		return elapsed();
	}

	template<class Time, class Duration, class Clock>
	void Timer<Time, Duration, Clock>::zero()
	{
		m_accumulated = std::chrono::duration<Duration, typename Time::period>::zero();
	}

	template<class Time, class Duration, class Clock>
	Duration Timer<Time, Duration, Clock>::elapsed() const
	{
		return m_accumulated.count();
	}

	template<class Time, class Duration, class Clock>
	template<class Callable, class ...Args>
	Duration Timer<Time, Duration, Clock>::latency(
		Callable c,
		Args &&... args)
	{
		Timer<Time, Duration, Clock> t;
		t.start();
		c(std::forward<Args>(args)...);
		return t.stop();
	}

	template<class Callable, class ...Args>
	Timer<>::duration_t latency(
		Callable c,
		Args &&... args)
	{
		return Timer<>::latency(
			std::forward<Callable>(c),
			std::forward<Args>(args)...);
	}
}