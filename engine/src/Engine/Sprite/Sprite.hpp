// Engine
// Ubisoft GameDev
// by Yevheniia Ksonzenko

#pragma once
#include <MiniKit/Graphics/Numerics.hpp>
#include <unordered_map>
#include "RectangleShape.hpp"
#include "Engine/World/World.hpp"

using Float2 = ::MiniKit::Graphics::float2;

namespace Engine
{
	class Sprite
	{
	public:
		Sprite() = default;
		Sprite(const ::std::string& textureName, const ::std::string& path);
		Sprite(const ::std::string& textureName, const ::std::string& path, const Float2 position, const Float2 size, const Float2 edges);

		RectangleShape& getRectangle() { return rectangle_; }
		MiniKit::Graphics::Image* getImage(const ::std::string& name);

	private:
		RectangleShape rectangle_;
	};
}
