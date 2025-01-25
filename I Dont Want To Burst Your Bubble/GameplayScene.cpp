#include "GameplayScene.h"

GameplayScene::GameplayScene()
{
	m_numPopped = 0;
	m_rows = 2;
	m_cols = 3;

	freshWrap(m_rows, m_cols);

	m_testBubble.setPosition({ 500.f, 500.f });

	m_gameTime = 0.0;
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
	m_gameTime += t_dT.asSeconds();

	float sin = generateSineWaveDelta(m_gameTime, 0.05f, 0.0f, 2.5f);
	float sin2 = generateSineWaveDelta(m_gameTime, 0.5, 0.0f, 0.5f);

	m_testBubble.move({ sin + sin2, 0.f });


}

void GameplayScene::render()
{
	m_window->clear(sf::Color::Black);

	for (auto& bub : m_bubbles) m_window->draw(bub);

	m_window->draw(m_testBubble);

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

float GameplayScene::generateSineWaveDelta(float t_time, float t_frequency, float t_phase, float t_amplitude)
{
	const float TWO_PI = 6.28318530718f;
	return t_amplitude * TWO_PI * t_frequency * cos(TWO_PI * t_frequency * t_time + t_phase) * (1.0f / 60.0f);
}
