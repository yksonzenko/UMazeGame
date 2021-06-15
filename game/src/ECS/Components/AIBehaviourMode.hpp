#pragma once
#include <map>
#include <MiniKit/Graphics/Numerics.hpp>

namespace GameEngine::ECS
{
	struct AIBehaviourMode
	{
		enum class Mode
		{
			WAITING,
			CHASE,
			SCATTER,
			FRIGHTENED,
			EATEN,
			Unknown
		};

		AIBehaviourMode(Mode aiMode) : currentMode_(aiMode) {}
		
		float duration{ 0.0f };
		float localTime_{ 0.0f };
		Mode currentMode_;
		::std::map<Mode, std::function<void()>> allAIBehaviours;
	};
}
