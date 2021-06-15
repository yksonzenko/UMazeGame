#pragma once
#include <entityx/entityx.h>
#include "Components/Transform.hpp"
#include "Components/Animation.hpp"
#include "Components/MapTileRenderer.hpp"
#include "Components/Lives.hpp"
#include "Components/Item.hpp"
#include "Events/GameOverEvent.hpp"
#include "Engine/World/World.hpp"
#include <MiniKit/MiniKit.hpp>

using namespace Engine;
namespace ex = entityx;

namespace GameEngine::ECS
{
	class RenderSystem : public ex::System<RenderSystem>, public ex::Receiver<RenderSystem>
	{
	public:
		RenderSystem();

		void configure(entityx::EventManager& events) override;
		void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
		void receive(const GameOverEvent& gameOver);

	private:
		::MiniKit::Engine::Context* context_;
		::MiniKit::Graphics::CommandBuffer* commandBuffer_;
		float delta{ 0.0f };
		bool gameOver_{ false };
	};
}
