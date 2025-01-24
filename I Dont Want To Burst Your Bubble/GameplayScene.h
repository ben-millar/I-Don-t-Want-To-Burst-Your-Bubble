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

    /// <summary>
    /// Creates a fresh new sheet of unpopped bubble wrap!
    /// </summary>
    /// <param name="t_rows">Number of rows of bubbles</param>
    /// <param name="t_cols">Number of columns of bubbles</param>
    void freshWrap(int t_rows, int t_cols);

    // Vector to store our tasty bubbles
    std::vector<Bubble> m_bubbles;

    // Track the number of bubbles popped
    int m_numPopped;

    // Tracks the rows/columns of bubble wrap
    float m_rows;
    float m_cols;
};

#endif
