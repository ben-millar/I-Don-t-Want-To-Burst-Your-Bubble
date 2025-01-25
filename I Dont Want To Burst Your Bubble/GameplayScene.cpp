#include "GameplayScene.h"

GameplayScene::GameplayScene()
{
	initMusic();
	initSoundBuffers();


	playMusic();

	m_numPopped = 0;
	m_rows = 1;
	m_cols = 1;

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


			for (Bubble& bub : m_bubbles)
			{
				if (bub.pop(m_finger.getPosition()))
				{
					float pitch = 1.0f + m_numPopped * 0.05f;

					m_popSound.setPitch(pitch);

					m_popSound.play();
					m_numPopped++;


					//m_violinSound.play();

					if (m_numPopped >= m_rows * m_cols)
					{
						m_newWrapSound.play();
						freshWrap(++m_rows, ++m_cols);
						m_numPopped = 0;
					}
				}
			}

			//if (std::any_of(m_bubbles.begin(), m_bubbles.end(),
			//	[&](auto& bub) { return bub.pop(m_finger.getPosition()); })
			//	&& ++m_numPopped >= m_rows * m_cols) {

			//	freshWrap(++m_rows, ++m_cols);
			//	m_numPopped = 0;
			//}
		}
	}
}

static int count{ 0 };

void GameplayScene::update(sf::Time t_dT)
{
	m_gameTime += t_dT.asSeconds();

	// Don't ask. I'm sorry.
	if (!(++count % 60)) m_arm.setPosition(m_arm.getPosition());

	float sin_prim = generateSineWaveDelta(m_gameTime, 0.05, 0.0, 2.5);
	float sin_sec = generateSineWaveDelta(m_gameTime, 0.333, 0.5, 0.5);

	float sin2_prim = generateSineWaveDelta(m_gameTime, 0.0333, 0.0, 2.5);
	float sin2_sec = generateSineWaveDelta(m_gameTime, 0.5, 0.5, 0.5);

	std::for_each(m_bubbles.begin(), m_bubbles.end(),
		[&](auto& bub) {
			bub.move({ sin_prim + sin_sec, sin2_prim + sin2_sec });
		});

	m_bubbleWrap.move({ sin_prim + sin_sec, sin2_prim + sin2_sec });

	// Set arm position
	sf::Vector2f mousePos = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
	m_finger.update(mousePos);
	m_arm.setPosition(m_finger.getPosition());

	// Set arm sprite
	m_arm.isClicking(sf::Mouse::isButtonPressed(sf::Mouse::Left));

}

void GameplayScene::render()
{
	m_window->clear(sf::Color {133, 193, 255});

	m_window->draw(m_bubbleWrap);

	for (auto& bub : m_bubbles) m_window->draw(bub);

	m_window->draw(m_arm);

	// We don't need to draw this other than for debugging purposes
	//m_window->draw(m_finger.getBody());

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

	// Calculate the size of the bubble wrap
	float wrapWidth = ((t_cols - 1) * offset);
	float wrapHeight = ((t_rows - 1) * offset);

	// Set the bubble wrap size and position
	m_bubbleWrap.setOrigin(offset/2, offset/2);
	m_bubbleWrap.setSize(sf::Vector2f(wrapWidth + offset, wrapHeight + offset));
	m_bubbleWrap.setPosition(400.f, 400.f);
	m_bubbleWrap.setFillColor(sf::Color { 131, 0, 4});
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
	m_music.setVolume(20);
}

void GameplayScene::stopMusic()
{
	m_music.stop();
}

void GameplayScene::initSoundBuffers()
{
	if (!m_popBuffer.loadFromFile("Assets/Sound/Pop.wav"))
	{
		std::cout << "Error loading pop sound file" << std::endl;
	}

	if (!m_violinBuffer.loadFromFile("Assets/Sound/Violin4.wav"))
	{
		std::cout << "Error loading violin sound file" << std::endl;
	}

	if (!m_newWrapBuffer.loadFromFile("Assets/Sound/NewWrap2.wav"))
	{
		std::cout << "Error loading wrap sound file" << std::endl;
	}

	m_popSound.setBuffer(m_popBuffer);
	m_violinSound.setBuffer(m_violinBuffer);
	m_newWrapSound.setBuffer(m_newWrapBuffer);

	m_popSound.setVolume(70);
	m_violinSound.setVolume(10);
	m_newWrapSound.setVolume(50);

}

void GameplayScene::gameOver()
{
	// Stop the current music
	m_music.stop();

	if (!m_music.openFromFile("Assets/Music/MusicSlowingDown.wav"))
	{
		std::cout << "Error loading game over music file" << std::endl;
	}

	m_music.setLoop(false);
	m_music.setVolume(30);
	m_music.play();
}