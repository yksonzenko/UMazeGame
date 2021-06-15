// Engine
// Ubisoft GameDev
// by Yevheniia Ksonzenko

#include "Timer.hpp"

namespace Engine
{
	void Timer::setGlobalTimer()
	{
		begin_ = ::std::chrono::high_resolution_clock::now();
	}

	float Timer::getGlobalTime()
	{
		end_ = ::std::chrono::high_resolution_clock::now();
		durationInSeconds_ = end_ - begin_;
		globalTime_ = durationInSeconds_.count();
		
		return globalTime_;
	}

	long long Timer::getFrames(const int interval, const int frames_count) const
	{
		using namespace std::chrono_literals;
		const auto end = std::chrono::high_resolution_clock::now();
		return (std::chrono::duration_cast<std::chrono::milliseconds>(end - begin_).count() / interval) % frames_count;
	}
}
