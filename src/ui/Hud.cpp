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

 
}

void Hud::update(int ammo, int health) {
    ammoText.setString("Ammo: " + std::to_string(ammo));
    healthText.setString("Health: " + std::to_string(health));
    
}

void Hud::render(sf::RenderWindow& window) {
    window.draw(ammoText);
    window.draw(healthText);
}

void Hud::setHealth(int hp) {
    health = hp;
    updateTexts();
}

void Hud::setAmmo(int current, int max) {
    currentAmmo = current;
    maxAmmo = max;
    updateTexts();
}

void Hud::updateTexts() {
    healthText.setString("Health: " + std::to_string(health));
    ammoText.setString("Ammo: " + std::to_string(currentAmmo) + " / " + std::to_string(maxAmmo));
}