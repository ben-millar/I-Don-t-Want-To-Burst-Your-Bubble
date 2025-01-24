#ifndef BASE_SCENE_H
#define BASE_SCENE_H

#include <SFML/Graphics/RenderWindow.hpp>

class BaseScene
{
public:

	BaseScene() = default;
	virtual ~BaseScene() = default;

	void setRenderWindow(std::shared_ptr<sf::RenderWindow> t_window) { m_window = t_window; }

	virtual void processEvents() = 0;

	virtual void update(sf::Time t_dT) = 0;

	virtual void render() = 0;

protected:

	std::shared_ptr<sf::RenderWindow> m_window;
};

#endif
