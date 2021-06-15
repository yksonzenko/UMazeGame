#pragma once
#include "Engine/EntityComponent//Actor.hpp"
#include "Engine/World/World.hpp"
#include "ECS/Components/Animation.hpp"
#include "ECS/Components/Collision.hpp"
#include "ECS/Components/AIMovement.hpp"
#include "ECS/Components/Transform.hpp"
#include "ECS/Components/AIBehaviourMode.hpp"

using namespace GameEngine::ECS;

namespace GameEngine
{
	class RedBlinky : public Engine::Actor
	{
	public:
		explicit RedBlinky(Engine::Scene* scene);
		void assignAllComponents() override;
		void fillComponents() override;

	private:
		void setAIMode(AIBehaviourMode::Mode mode);
	};
}
