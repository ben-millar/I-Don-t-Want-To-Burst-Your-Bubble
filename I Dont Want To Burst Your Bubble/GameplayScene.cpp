#include "GameplayScene.h"

GameplayScene::GameplayScene()
{
	m_numPopped = 0;
	m_rows = 2;
	m_cols = 3;

	freshWrap(m_rows, m_cols);
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
			sf::Vector2f worldPos = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));

			if (std::any_of(m_bubbles.begin(), m_bubbles.end(),
				[&](auto& bub) { return bub.pop(worldPos); })
				&& ++m_numPopped >= m_rows * m_cols) {

				freshWrap(++m_rows, ++m_cols);
				m_numPopped = 0;
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

void GameplayScene::freshWrap(int t_rows, int t_cols) {
	m_bubbles.clear();
	m_bubbles.reserve(t_rows * t_cols);

	float offset = 80.f;

	for (int col = 0; col < t_cols; ++col) {
		for (int row = 0; row < t_rows; ++row) {
			sf::Vector2f pos{
				100.f + col * offset,
				100.f + row * offset
			};
			m_bubbles.emplace_back(pos);
		}
	}
}
