// Engine
// Ubisoft GameDev
// by Yevheniia Ksonzenko

/**
* @author Yevheniia Ksonzenko
* @param viewport_ size and pos
* @param viewport.position is center position of a new viewport relative to the window
* @param viewport.size is width and height of a new viewport
*/

#pragma once
#include <MiniKit/MiniKit.hpp>
#include <glm/glm.hpp>
#include <iostream>

using Int2 = ::MiniKit::Graphics::int2;
using Float2 = ::MiniKit::Graphics::float2;

namespace Engine
{
	// ToDO: add scaling
	class ViewPort
	{
		struct RectSides
		{
			float left{ 0.0f };
			float right{ 0.0f };
			float top{ 0.0f };
			float bottom{ 0.0f };
		};
	
	public:
		ViewPort(::MiniKit::Engine::Context& context, ::MiniKit::Graphics::Rect2D<int> viewport);

		void setOffsets();
		[[nodiscard]] bool setPositions(Float2 point, Float2 objSize);
		
		bool setToViewPos(Float2 point, Float2 objSize);
		[[nodiscard]] ::MiniKit::Graphics::float2 getPosOnView() const { return renderPoint_; }
		
		void drawViewPortBoundaries(::MiniKit::Graphics::CommandBuffer& command_buffer);
		[[nodiscard]] ::MiniKit::Graphics::Rect2D<int> getViewSize() const { return viewport_; }

		Float2 setMapOffsets(::MiniKit::Graphics::uint2 mapSize, Float2 tileSize);
		[[nodiscard]] Float2 getMapOffsets() const { return mapOffsets_; }
		Float2 mapCoordConversion(Float2 mapOffsets, Float2 point, Float2 tileSize);
		Float2 getSimplePos(Float2 position);

	private:
		::MiniKit::Engine::Context& context_;
		::MiniKit::Graphics::Rect2D<int> viewport_{ {0, 0}, {0, 0} };

		Float2 renderPoint_{ 0.0f, 0.0f };
		RectSides viewOffsets_;
		Float2 mapOffsets_{0.0f, 0.0f };
		Float2 tileSize_{0.0f, 0.0f };

		// texture for viewport boundaries
		::std::unique_ptr<::MiniKit::Graphics::Image> testTexture_{ nullptr };
	};
}
