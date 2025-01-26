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

	void isClicking(bool t_isClicking);

	void setCramping(bool t_isCramping);

private:
	sf::Texture m_defaultTex;
	sf::Texture m_clickTex;
	sf::Texture m_crampTex;

	sf::Sprite m_arm;

	bool m_isCramping{ false };

	virtual void draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const override {
		t_target.draw(m_arm);
	}
};

#endif