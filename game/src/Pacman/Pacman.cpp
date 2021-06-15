#include "Pacman.hpp"

using namespace Engine;

namespace GameEngine
{
	Pacman::Pacman(Scene* scene) : Actor(scene)
	{
		assignAllComponents();

		fillComponents();
	}

	void Pacman::assignAllComponents()
	{
		entity_.assign<Animation>();
		entity_.assign<Movement>(Movement::Direction::STILL);
		entity_.assign<Collision>(0.5f);
		entity_.assign<Lives>(3);
		entity_.assign<PlayerBehaviourMode>(PlayerBehaviourMode::Mode::WALKING);
		entity_.assign<Item>();
		entity_.assign<Input>();
	}

	void Pacman::fillComponents()
	{
		auto transform = entity_.component<Transform>();
		transform->size = { 32, 32 };
		transform->scale = {24, 24};
		transform->position = { 13, 23 };
		transform->spawnPos = { 13, 23 };

		pacmanWalkingAnim();

		auto move = entity_.component<Movement>();
		move->distance = 1;
		move->speed = 0.06f;
		move->directionState.insert_or_assign(Movement::Direction::STILL, ::MiniKit::Graphics::int2{ 0, 0 });
		move->directionState.insert_or_assign(Movement::Direction::RIGHT, ::MiniKit::Graphics::int2{ move->distance, 0 });
		move->directionState.insert_or_assign(Movement::Direction::LEFT, ::MiniKit::Graphics::int2{ -move->distance, 0 });
		move->directionState.insert_or_assign(Movement::Direction::UP, ::MiniKit::Graphics::int2{ 0, -move->distance });
		move->directionState.insert_or_assign(Movement::Direction::DOWN, ::MiniKit::Graphics::int2{ 0, move->distance });

		auto lives = entity_.component<Lives>();
		auto* view = World::getWorld()->viewPort();
		lives->texture = World::getWorld()->textureManager()->getImage("pacman");
		lives->livesImage = { {64, 0}, {32, 32} };
		if (view->setToViewPos({ 130, 650 }, { 32, 32 }))
		{
			lives->spawnPosition = view->getPosOnView();
		}

		auto behaviour = entity_.component<PlayerBehaviourMode>();
		behaviour->allPlayerBehaviours = {
			{PlayerBehaviourMode::Mode::EATEN, [=]() {return eatenMode(); }},
			{PlayerBehaviourMode::Mode::WALKING, [=]() {return walkingMode(); }},
			{PlayerBehaviourMode::Mode::CHASING, [=]() {return chasingMode(); }},
			{PlayerBehaviourMode::Mode::IDLE, [=]() {return idleMode(); }}
		};
	}

	void Pacman::pacmanWalkingAnim()
	{
		auto anim = entity_.component<Animation>();
		anim->texture_ = World::getWorld()->textureManager()->getImage("pacman");
		anim->textureID = 1;
		anim->speed = 10ull;
		anim->texAmount = 2;
		anim->texCutSet_.position.y = 0;
		anim->texCutSet_.size = { 32, 32 };
	}

	void Pacman::pacmanEatenAnim()
	{
		auto anim = entity_.component<Animation>();
		anim->texture_ = World::getWorld()->textureManager()->getImage("allSpriteSet");
		anim->textureID = 1;
		anim->speed = 8ull;
		anim->texAmount = 11;
		anim->texCutSet_.position.x = 0;
		anim->texCutSet_.position.y = 0;
	}

	void Pacman::eatenMode()
	{
		auto behaviour = entity_.component<PlayerBehaviourMode>();
		behaviour->currentMode = PlayerBehaviourMode::Mode::EATEN;
		behaviour->duration = 1.5f;
		auto input = entity_.component<Input>();
		input->keyPressed_ = MiniKit::Platform::Keycode::Unknown;
		pacmanEatenAnim();

		auto lives = entity_.component<Lives>();
		lives->livesCount -= 1;
	}

	void Pacman::walkingMode()
	{
		auto behaviour = entity_.component<PlayerBehaviourMode>();
		behaviour->currentMode = PlayerBehaviourMode::Mode::WALKING;
		pacmanWalkingAnim();
	}

	void Pacman::idleMode()
	{
		auto behaviour = entity_.component<PlayerBehaviourMode>();
		behaviour->currentMode = PlayerBehaviourMode::Mode::IDLE;
		behaviour->duration = 3.0f;
		auto transform = entity_.component<Transform>();
		transform->position = transform->spawnPos;
		pacmanWalkingAnim();
	}

	void Pacman::chasingMode()
	{
		auto behaviour = entity_.component<PlayerBehaviourMode>();
		behaviour->currentMode = PlayerBehaviourMode::Mode::CHASING;
		pacmanWalkingAnim();
	}
}
