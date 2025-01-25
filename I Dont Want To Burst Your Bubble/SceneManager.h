#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <functional>
#include <memory>
#include <unordered_map>

#include "Globals.h"
#include "BaseScene.h"
#include "Finger.h"

enum class SceneType { GAMEPLAY };
using Scene = std::unique_ptr<BaseScene>;

class SceneManager
{
public:

	static SceneManager* getInstance() {
		static SceneManager instance;
		return &instance;
	}

	SceneManager(SceneManager const&) = delete;
	void operator=(SceneManager const&) = delete;

	void setRenderWindow(std::shared_ptr<sf::RenderWindow> t_window) { m_window = t_window; }

	template<typename T, typename... Args>
	void registerScene(SceneType t_sceneType, const Args& ...t_args) {
		m_sceneCache.emplace(t_sceneType, [t_args...]() {
			return std::make_unique<T>(t_args...);
		});
	}

	void setScene(SceneType t_sceneType) {
		if (const auto it = m_sceneCache.find(t_sceneType); it != m_sceneCache.end()) {
			m_currentScene = it->second();
			m_currentScene->setRenderWindow(m_window);
		}
		else {
			std::cerr << "Trying to create scene which hasn't been registered with SceneManager!" << std::endl;
		}
	}

	void processEvents() { m_currentScene->processEvents(); }
	void update(sf::Time t_dT) { m_currentScene->update(t_dT); }
	void render() { m_currentScene->render(); }

private:

	using SceneCache = std::unordered_map<SceneType, std::function<Scene()>>;

	SceneManager() {}
	SceneCache m_sceneCache;
	Scene m_currentScene;
	Finger m_finger;
	std::shared_ptr<sf::RenderWindow> m_window;

};

#endif
