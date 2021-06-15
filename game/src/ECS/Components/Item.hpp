#pragma once
#include <MiniKit/Graphics/Numerics.hpp>

namespace GameEngine::ECS
{
	struct Item
	{
		enum class ItemType
		{
			Dot,
			Pellet,
			Cherry,
			Unknown
		};

		struct Transform
		{
			bool visible{ false };
			::MiniKit::Graphics::float2 position{ 0.0f, 0.0f };
			::MiniKit::Graphics::float2 size{ 0.0f, 0.0f };
			int textureID{ -1 };
			int amount{ 0 };
			::MiniKit::Graphics::Rect2D<uint32_t> cutTexture{};
		};

		ItemType type;
		int amount{ 0 };
		int dotsAmount{ 0 };
		int pelletsAmount{ 0 };

		::std::vector<::MiniKit::Graphics::float2> bonuses_;
		::std::vector<Transform> cherryTransform_;
		::MiniKit::Graphics::Image* texture{};
	};
}