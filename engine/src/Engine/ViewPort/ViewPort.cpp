// Engine
// Ubisoft GameDev
// by Yevheniia Ksonzenko

#include "ViewPort.hpp"

namespace Engine
{
	ViewPort::ViewPort(::MiniKit::Engine::Context& context, ::MiniKit::Graphics::Rect2D<int> viewport) :
		context_(context), viewport_(viewport)
	{
		setOffsets();
	}
	
	void ViewPort::setOffsets()
	{
		viewOffsets_.left = viewport_.position.x - (viewport_.size.x / 2);
		viewOffsets_.right = viewport_.position.x + (viewport_.size.x / 2);
		viewOffsets_.top = viewport_.position.y + (viewport_.size.y / 2);
		viewOffsets_.bottom = viewport_.position.y - (viewport_.size.y / 2);
	}

	bool ViewPort::setPositions(Float2 point, Float2 objSize)
	{
		const auto coordinates = mapCoordConversion(mapOffsets_ , point, tileSize_);
		if (setToViewPos(coordinates, objSize))
		{
			return true;
		}
		return false;
	}
	
	bool ViewPort::setToViewPos(Float2 point, Float2 objSize)
	{
		if (point.x > viewport_.size.x - (objSize.x / 2) || point.x < (objSize.x / 2))
		{
			std::cout << "\033[0m[ERROR]\033[4;33m" << " render point X is out of viewport!\033[0m" << std::endl;
			return false;
		}
		if (point.y > viewport_.size.y - (objSize.y / 2) || point.y < (objSize.y / 2))
		{
			std::cout << "\033[0m[ERROR]\033[4;33m" << " render point Y is out of viewport!\033[0m" << std::endl;
			return false;
		}
		renderPoint_ = { (viewOffsets_.left + point.x), (viewOffsets_.top - point.y) };
		return true;
	}

	void ViewPort::drawViewPortBoundaries(::MiniKit::Graphics::CommandBuffer& command_buffer)
	{
		auto& grDev = context_.GetGraphicsDevice();
		testTexture_ = grDev.CreateImage("assets/square.png");

		command_buffer.SetImage(*testTexture_);
		::MiniKit::Graphics::DrawInfo drawable{};
		/* rendering point + half of image size */
		drawable.position = { static_cast<float>(renderPoint_.x + (viewport_.size.x / 2)), static_cast<float>(renderPoint_.y - (viewport_.size.y / 2)) };
		drawable.scale = { static_cast<float>(viewport_.size.x), static_cast<float>(viewport_.size.y) };
		command_buffer.Draw(drawable);
	}

	// setting map offsets regarding to the viewport
	Float2 ViewPort::setMapOffsets(::MiniKit::Graphics::uint2 mapSize, Float2 tileSize)
	{
		const auto viewportSize = getViewSize().size;
		tileSize_ = tileSize;
		mapOffsets_.x = (viewportSize.x - (mapSize.x * static_cast<int>(tileSize.x))) / 2;
		mapOffsets_.y = (viewportSize.y - (mapSize.y * static_cast<int>(tileSize.y))) / 2;
		return { mapOffsets_ };
	}

	Float2 ViewPort::mapCoordConversion(Float2 mapOffsets, Float2 point, Float2 tileSize)
	{
		float x = mapOffsets.x + (tileSize.x / 2) + tileSize.x * point.x;
		float y = mapOffsets.y + (tileSize.y / 2) + tileSize.y * point.y;
		return { x, y };
	}

	// Convert positions on viewport to positions according to tiled map
	Float2 ViewPort::getSimplePos(Float2 position)
	{
		const auto mapoffsets = getMapOffsets();
		
		const auto pXcoord = (position.x - mapoffsets.x - 8) / 16;
		const auto pYcoord = (position.y - mapoffsets.y - 8) / 16;
		return { pXcoord, pYcoord };
	}
}
