// Engine
// Ubisoft GameDev
// by Yevheniia Ksonzenko

#include "RectangleShape.hpp"

namespace Engine
{
	RectangleShape::RectangleShape(Float2 position, Float2 size, Float2 edges, float angle)
		: angle_(angle), position_(position), size_(size), edges_(edges) {}


	Float2* RectangleShape::getSize()
	{
		return &size_;
	}

	Float2* RectangleShape::getPosition()
	{
		return &position_;
	}

	Float2* RectangleShape::getEdges()
	{
		return &edges_;
	}

	float* RectangleShape::getAngel()
	{
		return &angle_;
	}
}
