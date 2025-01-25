#include "Arm.h"

#include <iostream>

Arm::Arm()
{
	if (!m_defaultTex.loadFromFile("Assets/Images/hand_default.png")) {
		std::cout << "Unable to load hand default :(" << std::endl;
	}

	if (!m_clickTex.loadFromFile("Assets/Images/hand_click.png")) {
		std::cout << "Unable to load hand default :(" << std::endl;
	}

	m_arm.setTexture(m_defaultTex);
	m_arm.setScale(-0.5f, 0.5f);
	m_arm.setOrigin({ m_arm.getLocalBounds().width * 0.73f, m_arm.getLocalBounds().height * 0.03f});
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
	float rotation = std::clamp(m_smoothedDelta * 40.f, -80.0f, 80.0f);
	m_arm.setRotation(rotation);
	m_arm.setPosition(t_position);
}

void Arm::isClicking(bool t_isClicking)
{
	if (t_isClicking) {
		m_arm.setTexture(m_clickTex);
		m_arm.setScale(-0.5f, 0.5f);
		m_arm.setOrigin({ m_arm.getLocalBounds().width * 0.73f, m_arm.getLocalBounds().height * 0.03f });
	}
	else {
		m_arm.setTexture(m_defaultTex);
		m_arm.setScale(-0.5f, 0.5f);
		m_arm.setOrigin({ m_arm.getLocalBounds().width * 0.73f, m_arm.getLocalBounds().height * 0.03f });
	}
}
