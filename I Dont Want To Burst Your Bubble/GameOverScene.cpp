#include "GameOverScene.h"

GameOverScene::GameOverScene()
{
	if (!m_bgTex.loadFromFile("Assets/Images/background.png")) {
		std::cout << "Unable to load background" << std::endl;
	}

	m_bgSprite.setTexture(m_bgTex);

	if (!m_gameOverTex.loadFromFile("Assets/Images/game_over.png")) {
		std::cout << "Unable to load game over" << std::endl;
	}

	m_gameOver.setTexture(m_gameOverTex);
	m_gameOver.setScale(0.8f, 0.8f);
	m_gameOver.setPosition({ 600.f, 100.f });

	if (!m_restartTex.loadFromFile("Assets/Images/restart.png")) {
		std::cout << "Unable to load restart button" << std::endl;
	}

	m_restartButton = new Button(m_restartTex, { 640.f, 720 });
	m_restartButton->setOnClick([]() {
		SceneManager::getInstance()->setScene(SceneType::MAIN_MENU);
		});

	m_arm.setCramping(false);

	setupFont();
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::processEvents()
{
	sf::Event event;

	while (m_window->pollEvent(event)) {
		if (sf::Event::Closed == event.type)
			m_window->close();

		if (sf::Event::KeyPressed == event.type) {
			if (event.key.code == sf::Keyboard::Escape) {
				m_window->close();
			}
		}

		if (m_restartButton->handleEvent(event, m_window)) return;
	}
}

void GameOverScene::update(sf::Time t_dT)
{
	// Set arm position
	sf::Vector2f mousePos = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
	m_finger.update(mousePos);
	m_arm.setPosition(m_finger.getPosition());

	// Set arm sprite
	m_arm.isClicking(sf::Mouse::isButtonPressed(sf::Mouse::Left));
}

void GameOverScene::render()
{
	m_window->clear();

	m_window->draw(m_bgSprite);
	m_window->draw(m_gameOver);

	m_window->draw(m_scoreText);

	m_window->draw(*m_restartButton);

	m_window->draw(m_arm);

	m_window->display();
}

void GameOverScene::setupFont()
{
	if (!m_font.loadFromFile("Assets/Font/BubFont.ttf"))
	{
		std::cout << "error with font file " << std::endl;
	}

	m_scoreText.setFont(m_font);
	m_scoreText.setCharacterSize(300);
	m_scoreText.setString(std::to_string(global_score));
	m_scoreText.setOrigin(m_scoreText.getLocalBounds().width / 2, m_scoreText.getLocalBounds().height / 2);
	m_scoreText.setFillColor(sf::Color(59, 38, 162));
	m_scoreText.setPosition(RESOLUTION.x * 0.1f, RESOLUTION.y * 0.33f);
}
