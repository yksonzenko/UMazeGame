#pragma once
#include <unordered_map>
#include <MiniKit/MiniKit.hpp>

namespace GameEngine::ECS
{
	struct Movement
	{
		enum class Direction
		{
			STILL,
			RIGHT,
			LEFT,
			UP,
			DOWN,
			Unknown
		};

		struct State
		{
			Direction direction;
			Direction nextDirection;
			::MiniKit::Graphics::float2 position;
		};
		
		Movement(Direction dir) : currentDir(dir) {}

		int distance{ 0 };
		float speed{ 0.0f };
		::std::unordered_map<Direction, ::MiniKit::Graphics::int2> directionState;
		Direction currentDir = Direction::STILL;
		State state{};
		
	};
}
