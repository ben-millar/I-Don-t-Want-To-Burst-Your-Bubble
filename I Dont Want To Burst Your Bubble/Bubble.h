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

	void move(sf::Vector2f t_delta) {
		m_body.setPosition(m_body.getPosition() + t_delta);
		m_bubbleSprite.setPosition(m_bubbleSprite.getPosition() + t_delta);
	}

	bool pop(sf::Vector2f t_mousePos);

private:
	sf::CircleShape m_body;
	float m_radius;

	bool m_isPopped;

	/// <summary>
	/// Sprite for the bubble
	/// </summary>
	sf::Sprite m_bubbleSprite;
	/// <summary>
	/// Texture for the bubble
	/// </summary>
	sf::Texture m_bubbleTexture;
	sf::Texture m_poppedTexture;

	virtual void draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const override {
		if (!m_isPopped) t_target.draw(m_body);
		t_target.draw(m_bubbleSprite, t_states);
	}
};

#endif