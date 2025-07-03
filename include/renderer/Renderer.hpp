#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics.hpp>

class Renderer {
public:
    virtual ~Renderer() = default;
    virtual void render(sf::RenderWindow& window) = 0;
};


#endif