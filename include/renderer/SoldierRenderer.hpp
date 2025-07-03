#ifndef SOLDIER_RENDERER_HPP
#define SOLDIER_RENDERER_HPP

#include <SFML/Graphics.hpp>
#include <renderer/Renderer.hpp>
#include <soldier/BaseSoldier.hpp>

class SoldierRenderer : public Renderer {
public:
    SoldierRenderer();
    void render(sf::RenderWindow& window, const BaseSoldier& soldier );
    void render(sf::RenderWindow& window) override;
private:
    sf::Texture soldierTexture;
    sf::Sprite SoldierSprite;
    sf::Vector2f defaultOrigin;
};

#endif