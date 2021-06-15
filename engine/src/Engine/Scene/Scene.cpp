// Engine
// Ubisoft GameDev
// by Yevheniia Ksonzenko

#include "Scene.hpp"

namespace Engine
{
	void Scene::setSceneName(const ::std::string& name)
	{
		sceneName_ = name;
	}

	::std::string& Scene::getSceneName()
	{
		return sceneName_;
	}

	::std::shared_ptr<Scene> SceneManager::findScene(const ::std::string& sceneName)
	{
		return sceneList_[sceneName];
	}

	bool SceneManager::setActiveScene(const ::std::string& sceneName)
	{
		const auto search = sceneList_.find(sceneName);

		if (search != sceneList_.end())
		{
			sceneList_[sceneName]->activate();
			std::cout << "\033[4;33mScene: " << sceneList_[sceneName]->getSceneName() << " activated\033[0m" << '\n';
		}
		else
		{
			::std::cout << "\033[0m[ERROR]\033[4;33m" << "Scene: " << sceneName << " does not exist\033[0m" << std::endl;
			return false;
		}
		return true;
	}

	void SceneManager::removeSceneFromList(const ::std::string& sceneName)
	{
		const auto search = sceneList_.find(sceneName);
		if (search != sceneList_.end())
		{
			sceneList_.erase(search);
		}
		else
		{
			::std::cout << "\033[0m[ERROR]\033[4;33m" << "Scene: " << sceneName << " does not exist\033[0m" << std::endl;
		}
	}

	void SceneManager::clearAllScenes()
	{
		if (!sceneList_.empty())
		{
			sceneList_.clear();
		}
	}

	void SceneManager::showSceneList()
	{
		for (auto a : sceneList_)
		{
			std::cout << "\- " << a.first << '\t' << "\033[4;33m" + a.second->getSceneName() + "\033[0m" << std::endl;
		}
	}

	void SceneManager::deactivateCurrentScene()
	{
		std::cout << sceneList_.size() << '\n';
		
		for (auto& scene : sceneList_)
		{
			if (scene.second->isActive())
			{
				scene.second->deactivate();
				std::cout << "\033[4;33mScene: " << scene.second->getSceneName() << " was deactivated\033[0m" << '\n';
			}
		}
	}

	void SceneManager::updateCurrentScene()
	{
		if (sceneList_.empty())
		{
			return;
		}
		for (auto& scene : sceneList_)
		{
			if (scene.second->isActive())
			{
				scene.second->update();
				break;
			}
		}
	}
}
