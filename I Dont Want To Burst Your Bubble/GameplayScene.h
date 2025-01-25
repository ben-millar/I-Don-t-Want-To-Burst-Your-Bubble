#ifndef GAMEPLAY_SCENE_H
#define GAMEPLAY_SCENE_H

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "BaseScene.h"
#include "Arm.h"
#include "Bubble.h"
#include "Finger.h"

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

    sf::RectangleShape m_bubbleWrap;


    /// <summary>
    /// Variable to store the background music
    /// </summary>
    sf::Music m_music;


    // finger
    Finger m_finger;


    /// <summary>
    /// Method to initialize the background music
    /// </summary>
    void initMusic();

    sf::Sound m_popSound;
    sf::Sound m_violinSound;
    sf::SoundBuffer m_popBuffer;
    sf::SoundBuffer m_violinBuffer;

    void gameOver();

    void initSoundBuffers();

    void playMusic();

    void stopMusic();

    /// <summary>
    /// Creates a fresh new sheet of unpopped bubble wrap!
    /// </summary>
    /// <param name="t_rows">Number of rows of bubbles</param>
    /// <param name="t_cols">Number of columns of bubbles</param>
    void freshWrap(int t_rows, int t_cols);

    /// <summary>
    /// This function generates the derivative of a sin wave at a given time point.
    /// I.e., rather than returning the absolute position of the wave, we return the
    /// direction it's moving.
    /// </summary>
    /// <param name="t_time">Delta time</param>
    /// <param name="t_frequency">Wave frequency (wave-to-wave peak time)</param>
    /// <param name="t_phase">Wave phase (I.e., offset)</param>
    /// <param name="t_amplitude">Amplitude of the wave (peak height)</param>
    /// <returns>The rate of change of the sine wave at the given timepoint</returns>
    float generateSineWaveDelta(double t_time, double t_frequency, double t_phase, double t_amplitude = 1.0f);

    // Vector to store our tasty bubbles
    std::vector<Bubble> m_bubbles;

    Arm m_arm;

    // Track the number of bubbles popped
    int m_numPopped;

    // Tracks the rows/columns of bubble wrap
    int m_rows;
    int m_cols;

    // Atomically increasing tracker of game time since start
    double m_gameTime;
};

#endif
