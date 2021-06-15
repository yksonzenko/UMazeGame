#pragma once
#include <MiniKit/Graphics/Numerics.hpp>

namespace GameEngine::ECS
{
	struct Transform
	{
		Transform(float rotationAngle = 0.0f,
			::MiniKit::Graphics::float2 position = { 0, 0 },
			::MiniKit::Graphics::float2 spawnPos = { 0, 0 },
			::MiniKit::Graphics::int2 direction = { 0, 0 },
			::MiniKit::Graphics::float2 scale = { 1.0f, 1.0f },
			::MiniKit::Graphics::float2 size = { 0.0f, 0.0f })
			: rotationAngle(rotationAngle), position(position), spawnPos(spawnPos), direction(direction), scale(scale), size(size) {}

		float rotationAngle;
		::MiniKit::Graphics::float2 position;
		::MiniKit::Graphics::float2 spawnPos;
		::MiniKit::Graphics::int2 direction;
		::MiniKit::Graphics::float2 scale;
		::MiniKit::Graphics::float2 size;
	};
}
