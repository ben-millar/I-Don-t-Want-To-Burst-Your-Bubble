#include "Arm.h"

#include <iostream>

Arm::Arm()
{
	m_arm.setFillColor(sf::Color::Magenta);
	m_arm.setSize({ 120.f, 1600.f });
	m_arm.setOrigin({ 60.f, 0.f });
}

Arm::Arm(sf::Vector2f t_position) : Arm()
{
	m_arm.setPosition(t_position);
}

// Keep a history for lerping
float m_smoothedDelta;

void Arm::setPosition(sf::Vector2f t_position)
{
	// We want to tilt the arm based on the delta pos (on x axis)
	float delta = t_position.x - m_arm.getPosition().x;
	m_smoothedDelta = m_smoothedDelta + (delta - m_smoothedDelta) * 0.1f;
	float rotation = std::clamp(m_smoothedDelta, -80.0f, 80.0f);
	m_arm.setRotation(rotation);
	m_arm.setPosition(t_position);
}
