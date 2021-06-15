#pragma once
#include <MiniKit/Graphics/Numerics.hpp>
#include <MiniKit/Graphics/Image.hpp>

namespace GameEngine
{
	struct Lives
	{
		Lives(uint32_t numLives) : livesCount(numLives) {}
		
		uint32_t livesCount{ 0 };
		::MiniKit::Graphics::float2 spawnPosition{ 0.0f, 0.0f };
		::MiniKit::Graphics::Image* texture{ nullptr };
		::MiniKit::Graphics::Rect2D<uint32_t> livesImage{};
	};
}
