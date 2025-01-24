#ifndef GAMEPLAY_SCENE_H
#define GAMEPLAY_SCENE_H

#include <SFML/Graphics.hpp>

#include "BaseScene.h"

class GameplayScene :
    public BaseScene
{
public:

    GameplayScene();
    ~GameplayScene();

    virtual void processEvents() override;

    virtual void update(sf::Time t_dT) override;

    virtual void render() override;

private:

    sf::CircleShape m_shape;
};

#endif
