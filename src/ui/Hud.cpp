#include <ui/Hud.hpp>
#include <stdexcept>
#include <iostream>


Hud::Hud() {

    if (!font.loadFromFile("../assets/fonts/open_sans/OpenSans.ttf")) {
        throw std::runtime_error("Failed to load font for HUD");
    }
    
    ammoText.setFont(font);
    ammoText.setCharacterSize(20);
    ammoText.setFillColor(sf::Color::Black);
    ammoText.setPosition(10, 10);

    healthText.setFont(font);
    healthText.setCharacterSize(20);
    healthText.setFillColor(sf::Color::Black);
    healthText.setPosition(10, 40);

    //Healthbar
    healthBarBg.setSize(sf::Vector2f(50,6));
    healthBarBg.setFillColor(sf::Color(50,50,50));
    healthBarBg.setOrigin(25, 6);

    healthBarFg.setSize(sf::Vector2f(50, 6));
    healthBarFg.setFillColor(sf::Color::Green);
    healthBarFg.setOrigin(25, 6);
 
}

void Hud::update(int ammo, int health) {
    ammoText.setString("Ammo: " + std::to_string(ammo));
    healthText.setString("Health: " + std::to_string(health));
    
}

void Hud::renderStatic(sf::RenderWindow& window) {
    window.draw(ammoText);
    window.draw(healthText);
}

void Hud::setHealth(int hp, int max) {
    health = hp;
    maxHealth = max;
    updateTexts();
}

void Hud::setAmmo(int current, int max) {
    currentAmmo = current;
    maxAmmo = max;
    updateTexts();
}

void Hud::updateTexts() {
    updateHealthBar();
    healthText.setString("Health: " + std::to_string(health));
    ammoText.setString("Ammo: " + std::to_string(currentAmmo) + " / " + std::to_string(maxAmmo));
}

void Hud::updateHealthBar() {
    float healthPercent = static_cast<float>(health) / maxHealth;
    healthBarFg.setSize(sf::Vector2f(50 * healthPercent, 6));
}

void Hud::renderPlayerHealthBar(sf::RenderWindow& window, const sf::Vector2f& playerPos) {
    healthBarBg.setPosition(playerPos.x, playerPos.y - 30);
    healthBarFg.setPosition(playerPos.x, playerPos.y - 30);

    window.draw(healthBarBg);
    window.draw(healthBarFg);
}