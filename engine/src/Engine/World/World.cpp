// Engine
// Ubisoft GameDev
// by Yevheniia Ksonzenko

#include "World.hpp"

namespace Engine
{
	World* World::world_ = nullptr;

	World* World::getWorld()
	{
		return world_ = world_ == nullptr ? new World() : world_;
	}

	void World::setContext(::MiniKit::Engine::Context* context)
	{
		context_ = context;
		sceneManager_ = new SceneManager();
		inputManager_ = new InputManager(context);
		viewport_ = new ViewPort(*context, { {0, 0}, {672, 752} });
		textureManager_ = new TextureManager(context);
		globalTime_ = new Timer();
		gameState_ = new FSM::StateMachine();
	}

	void World::setCommandBuffer(::MiniKit::Graphics::CommandBuffer* commandBuffer)
	{
		commandBuffer_ = commandBuffer;
	}
}
