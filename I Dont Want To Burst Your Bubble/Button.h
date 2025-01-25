#ifndef BUTTON_H
#define BUTTON_H

#include <functional>

#include <SFML/Graphics.hpp>

class Button : public sf::Drawable {
public:
    Button(sf::Texture& t_texture, sf::Vector2f t_pos) {
        m_sprite.setTexture(t_texture);
        m_sprite.setScale(0.8f, 0.8f);
        m_sprite.setPosition(t_pos);
    }

    template<typename F>
    void setOnClick(F&& callback) {
        m_onClick = std::forward<F>(callback);
    }

    bool handleEvent(const sf::Event& event, std::shared_ptr<sf::RenderWindow> t_window) {
        if (event.type == sf::Event::MouseButtonPressed
            && event.mouseButton.button == sf::Mouse::Left) {

            sf::Vector2f mousePos = t_window->mapPixelToCoords(
                sf::Vector2i(event.mouseButton.x, event.mouseButton.y)
            );

            if (m_sprite.getGlobalBounds().contains(mousePos)) {
                m_onClick();
                return true;
            }
        }

        return false;
    }

private:
    std::function<void()> m_onClick;
    sf::Sprite m_sprite;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(m_sprite, states);
    }
};

#endif