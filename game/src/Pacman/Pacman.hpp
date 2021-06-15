#pragma once
#include <MiniKit/Graphics/Numerics.hpp>
#include "Engine/EntityComponent/Actor.hpp"
#include "Engine/World/World.hpp"
#include "ECS/Components/Transform.hpp"
#include "ECS/Components/Animation.hpp"
#include "ECS/Components/Movement.hpp"
#include "ECS/Components/Collision.hpp"
#include "ECS/Components/Lives.hpp"
#include "ECS/Components/Item.hpp"
#include "ECS/Components/Input.hpp"
#include "ECS/Components/PlayerBehaviourMode.hpp"

using namespace GameEngine::ECS;

namespace GameEngine
{
	class Pacman final : public Engine::Actor
	{
	public:
		explicit Pacman(Engine::Scene* scene);

		void assignAllComponents() override;

		void fillComponents() override;

	private:
		void eatenMode();
		void walkingMode();
		void idleMode();
		void chasingMode();
		void pacmanWalkingAnim();
		void pacmanEatenAnim();
	};
}
