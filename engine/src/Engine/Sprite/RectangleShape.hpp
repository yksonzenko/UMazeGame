// Engine
// Ubisoft GameDev
// by Yevheniia Ksonzenko

#pragma once

#include <MiniKit/Graphics/Numerics.hpp>
#include "Engine/World/World.hpp"

using Float2 = ::MiniKit::Graphics::float2;

namespace Engine
{
	class RectangleShape
	{
	public:
		RectangleShape() = default;
		explicit RectangleShape(Float2 position, Float2 size, Float2 edges, float angle);

		Float2* getSize();
		Float2* getEdges();
		Float2* getPosition();
		float* getAngel();

	private:
		float angle_{ 0.0f };
		Float2 position_{ 0, 0 };
		Float2 size_{ 0.0f, 0.0f };
		Float2 edges_{ 0.0f, 0.0f };
	};
}
