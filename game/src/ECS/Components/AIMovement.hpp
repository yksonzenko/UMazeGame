#pragma once
#include <MiniKit/Graphics/Numerics.hpp>

namespace GameEngine::ECS
{
	struct AIMovement
	{
		enum class Direction
		{
			RIGHT,
			LEFT,
			UP,
			DOWN,
			Unknown
		};

		float moveDistance{ 0.0f };
		float speed{ 0.0f };
		float localTime{ 0.0f };
		::MiniKit::Graphics::float2 targetPos{ 0.0f, 0.0f };
		Direction currentDir_ = Direction::Unknown;
	};
}
