#include "Finger.h"


Finger::Finger()
{
	m_mouseDot.setRadius(5.0f);
	m_mouseDot.setOrigin(5.0f, 5.0f);
	m_mouseDot.setFillColor(sf::Color::Magenta);
	m_mouseDot.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}


void Finger::update(sf::Vector2f t_mousePosition)
{


	m_velocity = t_mousePosition - m_mouseDot.getPosition();

	m_length = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y); // pythagoras

	move(m_length);
}


void Finger::move(float t_length)
{

	if (t_length > m_speed)
	{
		m_velocity /= t_length;
		m_velocity *= m_speed*t_length; // extends vector
		m_location += m_velocity;

		// Keep within bounds
		float scaleX = WINDOW_WIDTH / RESOLUTION.x;
		float scaleY = WINDOW_HEIGHT / RESOLUTION.y;

		m_location.x = std::clamp(m_location.x, 0.f, RESOLUTION.x);
		m_location.y = std::clamp(m_location.y, 0.f, RESOLUTION.y);

		m_mouseDot.setPosition(m_location);
	}
}

sf::CircleShape Finger::getBody()
{
	return m_mouseDot;
}

sf::Vector2f Finger::getPosition()
{
	return m_mouseDot.getPosition();
}



