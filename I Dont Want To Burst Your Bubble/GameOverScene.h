#ifndef GAME_OVER_H
#define GAME_OVER_H

#include <SFML/Graphics.hpp>

#include "SceneManager.h"
#include "BaseScene.h"

#include "Button.h"

#include "Arm.h"

class GameOverScene :
    public BaseScene
{
public:
    GameOverScene();
    ~GameOverScene();

    virtual void processEvents() override;

    virtual void update(sf::Time t_dT) override;

    virtual void render() override;

private:
    sf::Texture m_bgTex;
    sf::Sprite m_bgSprite;

    sf::Texture m_gameOverTex;
    sf::Sprite m_gameOver;

    sf::Texture m_restartTex;
    Button* m_restartButton;

    Arm m_arm;
    Finger m_finger;
};

#endif