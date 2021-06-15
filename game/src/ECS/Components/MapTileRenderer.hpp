#pragma once
#include <MiniKit/Graphics/Numerics.hpp>
#include <MiniKit/Graphics/Image.hpp>
#include <map>
#include <vector>

namespace GameEngine::ECS
{
	struct MapTileRenderer
	{
		struct Transform
		{
			bool visible{ true };
			bool collidable{ false };
			bool tunnel{ false };
			float tileRotationAngle{ 0.0f };
			::MiniKit::Graphics::float2 tilePosition{ 0.0f, 0.0f };
			::MiniKit::Graphics::float2 tileScale{ 1.0f, 1.0f };
			::MiniKit::Graphics::float2 tileSize{ 0.0f, 0.0f };
			::std::vector<uint32_t> textureID;
			::MiniKit::Graphics::Rect2D<uint32_t> texCutSet{};
		};

		::MiniKit::Graphics::uint2 mapSize{ 0, 0 };
		::MiniKit::Graphics::float2 mapOffsets_;
		::std::vector<::MiniKit::Graphics::float2> randomPoints_;
		
		::std::vector<::std::vector<Transform>> transform_;
		::std::map<int, ::MiniKit::Graphics::Image*> mapTextures;
		::std::vector<::std::vector<::std::vector<int>>> mapLayersPack;
	};
}
