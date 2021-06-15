#pragma once
#include <MiniKit/Graphics/Numerics.hpp>
#include <entityx/entityx.h>
#include "Components/Transform.hpp"
#include "Components/MapTileRenderer.hpp"
#include "Events/CollisionEvent.hpp"
#include "Components/Movement.hpp"
#include "Components/Collision.hpp"
#include "Components/TunnelPath.hpp"

using Float2 = ::MiniKit::Graphics::float2;
using Int2 = ::MiniKit::Graphics::int2;

namespace GameEngine::ECS
{
	class CollisionSystem : public entityx::System<CollisionSystem>
	{
	public:
		CollisionSystem() = default;

		void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;

	private:
		static void onCollisionEvent(entityx::Entity& player, entityx::Entity& walls);
	};
}