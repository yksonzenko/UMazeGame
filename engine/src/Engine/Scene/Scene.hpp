// Engine
// Ubisoft GameDev
// by Yevheniia Ksonzenko

#pragma once

#include <entityx/entityx.h>
//#include <glm/glm.hpp>
#include <unordered_map>

namespace Engine
{
	class SceneManager;

	class Scene : public entityx::EntityX
	{
	public:
		virtual ~Scene() = default;
		
		void setSceneName(const ::std::string& name);
		::std::string& getSceneName();

		void activate() { sceneState_ = true; }
		void deactivate() { sceneState_ = false; }
		bool isActive() const { return sceneState_; }
		virtual void packScene() {};
		virtual void update() {};

	private:
		bool sceneState_{ false };
		::std::string sceneName_{};
	};

	class SceneManager
	{
	public:
		template<typename TScene, typename ... Args>
		std::shared_ptr<TScene> createScene(const std::string& sceneName, Args&&...args);

		::std::shared_ptr<Scene> findScene(const ::std::string& sceneName);
		::std::shared_ptr<Scene> getCurrentScene() const { return currentScene_; }
		bool setActiveScene(const ::std::string& sceneName);
		void deactivateCurrentScene();
		void updateCurrentScene();
		void removeSceneFromList(const ::std::string& sceneName);
		void clearAllScenes();
		void showSceneList();
		::std::unordered_map<std::string, ::std::shared_ptr<Scene>>& getScenePack() { return sceneList_; }
	
	private:
		::std::shared_ptr<Scene> currentScene_;
		::std::unordered_map<std::string, ::std::shared_ptr<Scene>> sceneList_;
	};

	template<typename TScene, typename ... Args>
	std::shared_ptr<TScene> SceneManager::createScene(const std::string& sceneName, Args&&...args)
	{
		if (sceneList_.count(sceneName) == 1)
		{
			return std::dynamic_pointer_cast<TScene>(sceneList_.at(sceneName));
		}
		std::shared_ptr<TScene> scene(new TScene(std::forward<Args>(args)...));
		sceneList_.emplace(sceneName, scene);
		sceneList_[sceneName]->setSceneName(sceneName);
		sceneList_[sceneName]->packScene();
		return scene;
	}
}
