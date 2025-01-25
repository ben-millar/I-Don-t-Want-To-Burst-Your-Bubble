#include "GameplayScene.h"

GameplayScene::GameplayScene()
{
	initMusic();
	playMusic();


	m_numPopped = 0;
	m_rows = 2;
	m_cols = 3;

	freshWrap(m_rows, m_cols);

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

	float sin_prim = generateSineWaveDelta(m_gameTime, 0.05, 0.0, 2.5);
	float sin_sec = generateSineWaveDelta(m_gameTime, 0.333, 0.5, 0.5);

	float sin2_prim = generateSineWaveDelta(m_gameTime, 0.0333, 0.0, 2.5);
	float sin2_sec = generateSineWaveDelta(m_gameTime, 0.5, 0.5, 0.5);

	std::for_each(m_bubbles.begin(), m_bubbles.end(),
		[&](auto& bub) {
			bub.move({ sin_prim + sin_sec, sin2_prim + sin2_sec });
		});

	sf::Vector2f worldPos = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));

	m_finger.update(worldPos);

}

void GameplayScene::render()
{
	m_window->clear(sf::Color {133, 193, 255});

	for (auto& bub : m_bubbles) m_window->draw(bub);
	
	m_window->draw(m_finger.getBody());

	m_window->display();
}

void GameplayScene::freshWrap(int t_rows, int t_cols) {
	m_bubbles.clear();
	m_bubbles.reserve(t_rows * t_cols);

	float offset = 80.f;

	for (int col = 0; col < t_cols; ++col) {
		for (int row = 0; row < t_rows; ++row) {
			sf::Vector2f pos{
				400.f + col * offset,
				400.f + row * offset
			};
			m_bubbles.emplace_back(pos);
		}
	}
}

float GameplayScene::generateSineWaveDelta(double t_time, double t_frequency, double t_phase, double t_amplitude)
{
	const float TWO_PI = 6.28318530718f;
	return static_cast<float>(t_amplitude * TWO_PI * t_frequency * cos(TWO_PI * t_frequency * t_time + t_phase) * (1.0f / 60.0f));
}

void GameplayScene::initMusic()
{
	if (!m_music.openFromFile("Assets/Music/Music.wav"))
	{
		std::cout << "Error loading music file" << std::endl;
	}

	m_music.setLoop(true);
}

void GameplayScene::playMusic()
{
	m_music.play();
}

void GameplayScene::stopMusic()
{
	m_music.stop();
}