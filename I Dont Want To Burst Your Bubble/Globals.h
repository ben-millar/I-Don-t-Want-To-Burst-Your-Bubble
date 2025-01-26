#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>

#define WINDOW_HEIGHT sf::VideoMode::getDesktopMode().height / 4 * 3
#define WINDOW_WIDTH WINDOW_HEIGHT * 16 / 9
#define RESOLUTION sf::Vector2f{ 1920.f, 1080.f }

#ifndef GLOBAL_SCORE_H
#define GLOBAL_SCORE_H
extern int global_score;
#endif

#endif
