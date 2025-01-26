#ifndef MENU_SCENE_H
#define MENU_SCENE_H

#include <array>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "SceneManager.h"
#include "BaseScene.h"
#include "Button.h"
#include "Arm.h"
#include "Finger.h"

class MenuScene :
	public BaseScene
{
public:
	MenuScene();
	~MenuScene();

	virtual void processEvents() override;

	virtual void update(sf::Time t_dT) override;

	virtual void render() override;

private:
	sf::Texture m_bgTex;
	sf::Sprite m_bg;

	sf::Texture m_mainLogoTex;
	
	sf::Texture m_playTex;
	sf::Texture m_controlsTex;
	sf::Texture m_exitTex;

	Button* m_playButton;
	Button* m_controlsButton;
	Button* m_exitButton;

	std::array<Button*, 3> m_buttons;

	Arm m_arm;
	Finger m_finger;
};

#endif