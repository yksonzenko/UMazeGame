#include "RedBlinky.hpp"

namespace GameEngine
{
	RedBlinky::RedBlinky(Engine::Scene* scene) : Actor(scene)
	{
		assignAllComponents();
		fillComponents();
	}

	void RedBlinky::assignAllComponents()
	{
		entity_.assign<Animation>();
		entity_.assign<AIMovement>();
		entity_.assign<AIBehaviourMode>(AIBehaviourMode::Mode::CHASE);
		entity_.assign<Collision>(0.5f);
	}

	void RedBlinky::fillComponents()
	{
		auto transform = entity_.component<Transform>();
		transform->position = { 13, 11 };
		transform->spawnPos = {13, 11};
		transform->size = { 32, 32 };
		transform->scale = { 26, 26 };

		auto anim = entity_.component<Animation>();
		anim->textureID = 1;
		anim->speed = 3ull;
		anim->texture_ = Engine::World::getWorld()->textureManager()->getImage("allSpriteSet");
		anim->visible = true;

		auto behav = entity_.component<AIBehaviourMode>();
		behav->allAIBehaviours = {
			{AIBehaviourMode::Mode::CHASE, [=]() {return setAIMode(AIBehaviourMode::Mode::CHASE); }},
			{AIBehaviourMode::Mode::EATEN, [=]() {return setAIMode(AIBehaviourMode::Mode::EATEN); }},
			{AIBehaviourMode::Mode::FRIGHTENED, [=]() {return setAIMode(AIBehaviourMode::Mode::FRIGHTENED); }},
			{AIBehaviourMode::Mode::SCATTER, [=]() {return setAIMode(AIBehaviourMode::Mode::SCATTER); }},
			{AIBehaviourMode::Mode::WAITING, [=]() {return setAIMode(AIBehaviourMode::Mode::WAITING); }},
			{AIBehaviourMode::Mode::Unknown, [=]() {return setAIMode(AIBehaviourMode::Mode::Unknown); }},
		};
		setAIMode(behav->currentMode_);
	}
	
	void RedBlinky::setAIMode(AIBehaviourMode::Mode mode)
	{
		auto transform = entity_.component<Transform>();
		auto anim = entity_.component<Animation>();
		auto ai = entity_.component<AIMovement>();
		auto behaviour = entity_.component<AIBehaviourMode>();

		behaviour->currentMode_ = mode;
		
		if (mode == AIBehaviourMode::Mode::CHASE)
		{
			anim->texAmount = 2;
			anim->texCutSet_ = { {0, 32}, {32, 32} };
			ai->speed = 0.15f;
			behaviour->duration = 20.0f;
		}

		if (mode == AIBehaviourMode::Mode::SCATTER)
		{
			anim->texAmount = 2;
			anim->texCutSet_ = { {0, 32}, {32, 32} };
			ai->speed = 0.15f;
			behaviour->duration = 7.0f;
		}
		
		if (mode == AIBehaviourMode::Mode::Unknown)
		{
			anim->visible = false;
			transform->position = transform->spawnPos;
			ai->targetPos = { -1.0f, -1.0f };
			behaviour->duration = 0.7f;
		}

		if (mode == AIBehaviourMode::Mode::WAITING)
		{
			anim->texAmount = 2;
			anim->texCutSet_ = { {0, 32}, {32, 32} };
			anim->visible = true;
			transform->position = transform->spawnPos;
			ai->targetPos = {-1.0f, -1.0f};
			behaviour->duration = 0.7;
		}
		
		if (mode == AIBehaviourMode::Mode::FRIGHTENED)
		{
			anim->texAmount = 2;
			anim->texCutSet_ = { {0, 160}, {32, 32} };
			ai->speed = 0.2f;
			behaviour->duration = 5.0f;
		}
		
		if (mode == AIBehaviourMode::Mode::EATEN)
		{
			anim->texAmount = 1;
			anim->texCutSet_ = { {0, 128}, {32, 32} };
			ai->speed = 0.05f;
			ai->targetPos = transform->spawnPos;
			behaviour->duration = 1.5f;
		}
	}
}
