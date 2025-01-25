#ifndef ARM_H
#define ARM_H

#include <SFML/Graphics.hpp>

class Arm : public sf::Drawable
{
public:
	Arm();
	Arm(sf::Vector2f t_position);

	~Arm() = default;

	void setPosition(sf::Vector2f t_position);
	sf::Vector2f getPosition() { return m_arm.getPosition(); }

private:
	sf::Texture m_armTex;
	sf::Sprite m_arm;

	virtual void draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const override {
		t_target.draw(m_arm);
	}
};

#endif