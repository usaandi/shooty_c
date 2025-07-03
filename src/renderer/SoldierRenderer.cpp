#include <renderer/SoldierRenderer.hpp>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

SoldierRenderer::SoldierRenderer() {
    if(!soldierTexture.loadFromFile("../assets/sprites/soldier-right.png")) {
        throw std::runtime_error("Failed to load soldierRight.png");
    }
    SoldierSprite.setTexture(soldierTexture);

    sf::FloatRect bounds = SoldierSprite.getLocalBounds();
    defaultOrigin.x = soldierTexture.getSize().x / 2.f;
    defaultOrigin.y = soldierTexture.getSize().y / 2.f;
    SoldierSprite.setOrigin(defaultOrigin);
}

void SoldierRenderer::render(sf::RenderWindow& window, const BaseSoldier& soldier) {
    sf::Sprite sprite;
    //Transparent color for sprite
    sprite.setColor(sf::Color(255,255,255,128));
    sprite.setTexture(soldierTexture);
    sprite.setOrigin(defaultOrigin);

    sprite.setRotation(soldier.getSoldierRotation());
    sprite.setPosition(soldier.getSoldierPosition());

    // Create a rectangle drawing hitBox around each soldier for testing
    sf::RectangleShape hitBox;
    hitBox.setPosition(soldier.getSoldierPosition()); // Top-left corner at (100, 100)
    hitBox.setSize(sf::Vector2f(50, 50));// 50x50 rectangle
    hitBox.setOrigin(defaultOrigin); 
    hitBox.setOutlineThickness(1);
    hitBox.setOutlineColor(sf::Color::Black);
    window.draw(hitBox);
    window.draw(sprite);
}

// This is the required override!
void SoldierRenderer::render(sf::RenderWindow& window) {
    // Can leave this empty or provide a default render behavior
}