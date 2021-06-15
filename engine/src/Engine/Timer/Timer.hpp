// Engine
// Ubisoft GameDev
// by Yevheniia Ksonzenko

#pragma once
#include <chrono>

namespace Engine
{
	class Timer
	{
	public:
		void setGlobalTimer();
		float getGlobalTime();
		[[nodiscard]] float getCurrentTime() const { return globalTime_; }

		[[nodiscard]] long long getFrames(int interval, int frames_count) const;

	protected:
		::std::chrono::high_resolution_clock::time_point begin_, end_;
		::std::chrono::duration<float> durationInSeconds_{0.0f};
		float globalTime_{ 0.0f };
		float localTime_{ 0.0f };
	};
}
