#ifndef BUBBLE_H
#define BUBBLE_H

#include <SFML/Graphics.hpp>

class Bubble : public sf::Drawable
{
public:
	Bubble();
	Bubble(sf::Vector2f t_position);

	~Bubble() = default;

	void setPosition(sf::Vector2f t_position) {
		m_body.setPosition(t_position);
	}

	bool pop(sf::Vector2f t_mousePos);

private:
	sf::CircleShape m_body;
	float m_radius;

	bool m_isPopped;

	virtual void draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const override {
		t_target.draw(m_body);
	}
};

#endif