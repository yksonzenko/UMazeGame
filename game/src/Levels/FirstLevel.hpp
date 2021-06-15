#pragma once
#include "Engine/World/World.hpp"
#include "Engine/Scene/Scene.hpp"
#include "Map/Map.hpp"
#include "Pacman/Pacman.hpp"
#include "Ghosts/RedBlinky.hpp"
#include "Ghosts/PinkPinky.hpp"
#include "Score/Score.hpp"
#include "SecondLevel.hpp"

#include "ECS/Systems/LevelControlSystem.hpp"
#include "ECS/Systems/PlayerInputControlSystem.hpp"
#include "ECS/Systems/MovementSystem.hpp"
#include "ECS/Systems/CollisionSystem.hpp"
#include "ECS/Systems/AIMovementSystem.hpp"
#include "ECS/Systems/BehaviourSystem.hpp"
#include "ECS/Systems/ItemsCollectionSystem.hpp"
#include "ECS/Systems/RenderSystem.hpp"

namespace GameEngine::Levels
{
	class FirstLevel : public Scene
	{
	public:
		FirstLevel(Score* score);
		
		void packScene() override;

		void update() override;

	private:
		::std::shared_ptr<Map> map_{};
		::std::shared_ptr<Pacman> pacman_{};
		::std::shared_ptr<RedBlinky> redBlinky_{};
		::std::shared_ptr<PinkPinky> pinkPinky_{};
		::MiniKit::Engine::Context* context_;
		Score* gameScore_{nullptr};
	};
}
