#pragma once
#include <MiniKit/Graphics/Image.hpp>
#include <MiniKit/Graphics/Numerics.hpp>

namespace GameEngine::ECS
{
	struct Animation
	{
		Animation() = default;

		bool visible{ true };
		bool looping{ true };
		uint64_t speed{ 1 };
		uint64_t texAmount{ 1 };
		float duration{ 0.0f };
		::MiniKit::Graphics::Image* texture_{ nullptr };
		uint32_t textureID{ 0 };
		::MiniKit::Graphics::Rect2D<uint32_t> texCutSet_{};
	};
}
