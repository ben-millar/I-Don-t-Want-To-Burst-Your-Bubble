#include "GameplayScene.h"

GameplayScene::GameplayScene()
{
	for (int col = 0; col < 5; ++col) {
		for (int row = 0; row < 5; ++row) {
			sf::Vector2f pos{ 100.f + col * 80.f, 100.f + row * 80.f };
			m_bubbles.emplace_back(Bubble(pos));
		}
	}
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

		if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);
			sf::Vector2f worldPos = m_window->mapPixelToCoords(mousePos);

			for (auto& bub : m_bubbles) {
				bub.pop(worldPos);
			}
		}
	}
}

void GameplayScene::update(sf::Time t_dT)
{
}

void GameplayScene::render()
{
	m_window->clear(sf::Color::Black);

	for (auto& bub : m_bubbles) m_window->draw(bub);

	m_window->display();
}
