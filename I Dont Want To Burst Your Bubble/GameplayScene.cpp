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

	setupFont();
	setupCooldown();
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

		if (canClick && event.type == sf::Event::MouseButtonPressed) { // if not on cooldown
			if (std::any_of(m_bubbles.begin(), m_bubbles.end(),
				[&](auto& bub) { return bub.pop(m_finger.getPosition()); })
				&& ++m_numPopped >= m_rows * m_cols) {

				freshWrap(++m_rows, ++m_cols);
				m_numPopped = 0;
			}

			if (m_cdNum < m_maxCd - m_cdIncrement) // increment cool down bar value unless max value
			{
				m_cdNum += m_cdIncrement;
				m_cooldownBar.setSize(sf::Vector2f(m_cdNum, m_cdHeight));
			}
			else
			{
				m_cdNum = m_maxCd;
				canClick = false;
				m_cooldownBar.setFillColor(sf::Color::Red);
			}
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

	// Update cooldown

	if (canClick) // faster decrement for when you cant click (cooldown)
	{
		// Set arm sprite
		m_arm.isClicking(sf::Mouse::isButtonPressed(sf::Mouse::Left));

		if (m_cdNum >= 0 + m_cdDecrement * t_dT.asSeconds()) // decrement cooldown value unless minimal value
		{
			m_cdNum -= m_cdDecrement * t_dT.asSeconds();
		}
		else
		{
			m_cdNum = 0;
		}

		m_cooldownBar.setSize(sf::Vector2f(m_cdNum, m_cdHeight));

	}
	else // faster decrementing
	{
		// Set arm sprite
		m_arm.isClicking(false);

		if (m_cdNum > 0 + m_cdFasterDecrement * t_dT.asSeconds())
		{
			m_cdNum -= m_cdFasterDecrement * t_dT.asSeconds();
		}
		else
		{
			m_cdNum = 0;
			canClick = true; // if decrement reaches 0, cooldown is done
			m_cooldownBar.setFillColor(sf::Color::Yellow);

		}
		m_cooldownBar.setSize(sf::Vector2f(m_cdNum, m_cdHeight));
	}

	m_cooldownBar.setPosition(m_finger.getPosition().x + m_cdBarXOffset, m_finger.getPosition().y + m_cdBarYOffset);


}

void GameplayScene::render()
{
	m_window->clear(sf::Color {133, 193, 255});

	m_window->draw(m_bubbleWrap);

	for (auto& bub : m_bubbles) m_window->draw(bub);

	m_window->draw(m_arm);

	// We don't need to draw this other than for debugging purposes
	m_window->draw(m_finger.getBody());

	m_window->draw(m_text);
	m_window->draw(m_cooldownBar);

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
}

void GameplayScene::stopMusic()
{
	m_music.stop();
}

void GameplayScene::setupFont()
{
	if (!m_font.loadFromFile("Assets/Font/BubFont.ttf"))
	{
		std::cout << "error with font file " << std::endl;
	}

	m_text.setFont(m_font);
	m_text.setCharacterSize(40);
	m_text.setString("TEST of text");
	m_text.setOrigin(m_text.getLocalBounds().width/2, m_text.getLocalBounds().height / 2);
	m_text.setFillColor(sf::Color::Black);
	m_text.setPosition(RESOLUTION.x/2,RESOLUTION.y/2);
}

void GameplayScene::setupCooldown()
{
	m_cooldownBar.setFillColor(sf::Color::Yellow);
	m_cooldownBar.setSize(sf::Vector2f(m_cdNum, m_cdHeight));
	m_cooldownBar.setPosition(m_finger.getPosition().x + m_cdBarXOffset, m_finger.getPosition().y + m_cdBarYOffset);
}
