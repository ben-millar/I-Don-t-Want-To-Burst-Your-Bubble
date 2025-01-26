#include "MenuScene.h"

MenuScene::MenuScene()
{
	if (!m_bgTex.loadFromFile("Assets/Images/background.png")) {
		std::cout << "Unable to load background" << std::endl;
	}

	if (!m_playTex.loadFromFile("Assets/Images/play_button.png")) {
		std::cout << "Unable to load play button" << std::endl;
	}

	if (!m_controlsTex.loadFromFile("Assets/Images/controls_button.png")) {
		std::cout << "Unable to load controls button" << std::endl;
	}

	if (!m_exitTex.loadFromFile("Assets/Images/exit_button.png")) {
		std::cout << "Unable to load exit button" << std::endl;
	}

	m_bg.setTexture(m_bgTex);

	m_playButton = new Button(m_playTex, { 1000.f, 100.f });
	m_playButton->setOnClick([]() {
		SceneManager::getInstance()->setScene(SceneType::GAMEPLAY);
	});

	m_controlsButton = new Button(m_controlsTex, { 1000.f, 400.f });
	m_controlsButton->setOnClick([]() {
		std::cout << "Clicked controls" << std::endl;
	});

	m_exitButton = new Button(m_exitTex, { 1000.f, 700.f });
	m_exitButton->setOnClick([&]() {
		m_window->close();
	});

	m_buttons = {
		m_playButton,
		m_controlsButton,
		m_exitButton
	};
}

MenuScene::~MenuScene()
{
	std::for_each(m_buttons.begin(), m_buttons.end(),
		[&](auto* button) { delete button; }
	);
}

void MenuScene::processEvents()
{
	sf::Event event;

	while (m_window->pollEvent(event)) {
		if (sf::Event::Closed == event.type)
			m_window->close();

		//if (sf::Event::KeyPressed == event.type) {
		//	if (event.key.code == sf::Keyboard::Escape) {
		//		m_window->close();
		//	}
		//}

		for (auto& button : m_buttons) {
			if (button->handleEvent(event, m_window)) return;
		}
	}
}

void MenuScene::update(sf::Time t_dT)
{
	// Set arm position
	sf::Vector2f mousePos = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
	m_finger.update(mousePos);
	m_arm.setPosition(m_finger.getPosition());

	// Set arm sprite
	m_arm.isClicking(sf::Mouse::isButtonPressed(sf::Mouse::Left));
}

void MenuScene::render()
{
	m_window->clear();

	m_window->draw(m_bg);

	std::for_each(m_buttons.begin(), m_buttons.end(),
		[&](auto button) { m_window->draw(*button); }
	);

	m_window->draw(m_arm);

	m_window->display();
}
