#pragma once
#include <MiniKit/Graphics/Numerics.hpp>

namespace GameEngine::ECS
{	
	struct TargetingEvent
	{
		enum Type
		{
			Unknown,
			ENEMY,
			BONUS
		};
		
		TargetingEvent(::MiniKit::Graphics::float2& targetPosition, Type& targetType)
			: targetPos(targetPosition), type(targetType) {}

		::MiniKit::Graphics::float2 targetPos;
		Type type;
	};
}
