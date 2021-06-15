#pragma once
#include <map>
#include <functional>

namespace GameEngine::ECS
{
	struct PlayerBehaviourMode
	{
		enum class Mode
		{
			WALKING,
			EATEN,
			CHASING,
			IDLE,
			Unknown
		};

		PlayerBehaviourMode(Mode plM) : currentMode(plM) {}

		float duration{ 0.0f };
		Mode currentMode;
		::std::map<Mode, std::function<void()>> allPlayerBehaviours;
	};
}