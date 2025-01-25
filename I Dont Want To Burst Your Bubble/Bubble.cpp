#include "Bubble.h"

Bubble::Bubble()
{
	m_bubbleTexture.loadFromFile("Assets/Images/bubble.png");
	m_poppedTexture.loadFromFile("Assets/Images/bubble_popped.png");

	m_bubbleSprite.setTexture(m_bubbleTexture);
	m_bubbleSprite.setOrigin(
		m_bubbleSprite.getGlobalBounds().width / 2.0f,
		m_bubbleSprite.getGlobalBounds().height / 2.0f
	);
	m_bubbleSprite.setScale(0.1f, 0.1f);
	
	m_radius = 20.f;
	m_body.setRadius(m_radius);
	m_body.setOrigin(m_radius, m_radius);
	m_body.setFillColor(sf::Color::Red);

	m_isPopped = false;
}

Bubble::Bubble(sf::Vector2f t_position) : Bubble()
{
	m_body.setPosition(t_position);
	m_bubbleSprite.setPosition(t_position);
}

bool Bubble::pop(sf::Vector2f t_mousePos)
{
	if (m_isPopped) return false;

	sf::Vector2f distance = m_body.getPosition() - t_mousePos;
	float magnitude = std::sqrt(distance.x * distance.x + distance.y * distance.y);

	if (magnitude < m_radius) {
		m_isPopped = true;

		m_bubbleSprite.setTexture(m_poppedTexture);
		m_body.setFillColor(sf::Color::Blue);

		return true;
	}

	return false;
}
