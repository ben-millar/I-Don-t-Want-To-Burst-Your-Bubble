#include "GameplayScene.h"

GameplayScene::GameplayScene()
{
	m_shape.setFillColor(sf::Color::Red);
	m_shape.setRadius(40.f);
}

GameplayScene::~GameplayScene()
{
}

void GameplayScene::processEvents()
{
	sf::Event event;

	while (m_window->pollEvent(event)) {
		if (sf::Event::Closed == event.type)
			m_window->close();

		if (sf::Event::KeyPressed == event.type) {
			m_window->close();
		}
	}
}

void GameplayScene::update(sf::Time t_dT)
{
}

void GameplayScene::render()
{
	m_window->clear(sf::Color::Black);

	m_window->draw(m_shape);

	m_window->display();
}
