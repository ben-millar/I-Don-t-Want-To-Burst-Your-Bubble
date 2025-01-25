#include "Game.h"

void Game::run()
{
	init();

	auto sceneManager = SceneManager::getInstance();
	sceneManager->setRenderWindow(m_window);

	sceneManager->registerScene<GameplayScene>(SceneType::GAMEPLAY);

	sceneManager->setScene(SceneType::GAMEPLAY);

	sf::Clock clock;
	sf::Time lag = sf::Time::Zero;
	const sf::Time MS_PER_UPDATE = sf::seconds(1 / 60.f);

	while (m_window->isOpen()) {
		sf::Time dT = clock.restart();
		lag += dT;

		sceneManager->processEvents();

		while (lag > MS_PER_UPDATE) {
			sceneManager->update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}

		sceneManager->update(dT);
		sceneManager->render();
	}
}

void Game::init()
{
	m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "I (Don't) Want To Burst Your Bubble", sf::Style::Titlebar | sf::Style::Close);
	m_window->setKeyRepeatEnabled(false);
	m_window->setView({ RESOLUTION / 2.f, RESOLUTION });
	m_window->setMouseCursorVisible(false);
}
