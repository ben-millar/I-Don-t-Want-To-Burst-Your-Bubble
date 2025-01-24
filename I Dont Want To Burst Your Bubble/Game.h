#ifndef GAME_H
#define GAME_H

#include <memory>

#include <SFML/Graphics.hpp>

#include "Globals.h"
#include "GameplayScene.h"
#include "SceneManager.h"

class Game
{
public:

	Game() = default;
	~Game() = default;

	void run();

private:

	void init();

	std::shared_ptr<sf::RenderWindow> m_window;
};

#endif
