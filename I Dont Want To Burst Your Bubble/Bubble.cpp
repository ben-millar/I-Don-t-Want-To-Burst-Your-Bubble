#include "Bubble.h"

Bubble::Bubble()
{
	m_radius = 20.f;
	m_body.setRadius(m_radius);
	m_body.setOrigin(m_radius, m_radius);
	m_body.setFillColor(sf::Color::Red);

	m_isPopped = false;
}

Bubble::Bubble(sf::Vector2f t_position) : Bubble()
{
	m_body.setPosition(t_position);
}

bool Bubble::pop(sf::Vector2f t_mousePos)
{
	if (m_isPopped) return false;

	sf::Vector2f distance = m_body.getPosition() - t_mousePos;
	float magnitude = std::sqrt(distance.x * distance.x + distance.y * distance.y);

	if (magnitude < m_radius) {
		m_isPopped = true;
		m_body.setFillColor(sf::Color::Blue);

		return true;
	}

	return false;
}
