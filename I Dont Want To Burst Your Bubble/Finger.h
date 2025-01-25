#pragma once


#include "SFML/Graphics.hpp" 
#include "SFML/Audio.hpp" 
#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>   // supports ctime function
#include "Globals.h"



class Finger
{
public:

	Finger();
	void update(sf::Vector2f t_mousePosition);
	void move(float t_length);
	sf::CircleShape getBody();


private:

	sf::CircleShape m_mouseDot; // circle

	float length; // 

	sf::Vector2f m_velocity;
	sf::Vector2f m_location;

	float m_speed{ 0.17f };


};

