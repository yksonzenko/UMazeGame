// Engine
// Ubisoft GameDev
// by Yevheniia Ksonzenko

#pragma once
#include <MiniKit/MiniKit.hpp>
#include "Engine/Scene/Scene.hpp"
#include "Engine/InputManager/InputManager.hpp"
#include "Engine/TextureManager/TextureManager.hpp"
#include "Engine/ViewPort/ViewPort.hpp"
#include "Engine/Timer/Timer.hpp"
#include "FSM/StateMachine.hh"

namespace Engine
{
	class World
	{
	public:
		static World* getWorld();

		void setContext(::MiniKit::Engine::Context* context);
		void setCommandBuffer(::MiniKit::Graphics::CommandBuffer* commandBuffer);
		[[nodiscard]] ::MiniKit::Engine::Context* getContext() const { return context_; }
		[[nodiscard]] ::MiniKit::Graphics::CommandBuffer* getCommandBuffer() const { return commandBuffer_; }
		
		[[nodiscard]] SceneManager* sceneManager() const { return sceneManager_; }
		[[nodiscard]] InputManager* inputManager() const { return inputManager_; }
		[[nodiscard]] ViewPort* viewPort() const { return viewport_; }
		[[nodiscard]] TextureManager* textureManager() const { return textureManager_; }
		[[nodiscard]] Timer* globalTime() const { return globalTime_; }
		[[nodiscard]] FSM::StateMachine* gameState() const { return gameState_; }

	private:
		static World* world_;
		World() = default;
		::MiniKit::Engine::Context* context_;
		::MiniKit::Graphics::CommandBuffer* commandBuffer_;

		SceneManager* sceneManager_;
		InputManager* inputManager_;
		ViewPort* viewport_;
		TextureManager* textureManager_;
		Timer* globalTime_;
		FSM::StateMachine* gameState_;
	};
}
