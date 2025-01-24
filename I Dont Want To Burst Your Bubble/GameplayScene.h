#ifndef GAMEPLAY_SCENE_H
#define GAMEPLAY_SCENE_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "BaseScene.h"
#include "Bubble.h"

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

    std::vector<Bubble> m_bubbles;
};

#endif
