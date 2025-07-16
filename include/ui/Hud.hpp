#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>

class Hud {
public:
    Hud();
    
    void update(int ammo , int health);
    void renderPlayerHealthBar(sf::RenderWindow& window, const sf::Vector2f& playerPos);
    void renderStatic(sf::RenderWindow& window);
    void setHealth(int hp, int max);
    void setAmmo(int current, int max);
    void updateHealthBar();

private:
    sf::Font font;
    sf::Text ammoText;
    sf::Text healthText;
    sf::RectangleShape healthBarBg;
    sf::RectangleShape healthBarFg;
    int health = 100;
    int currentAmmo = 30;
    int maxAmmo = 30;
    int maxHealth = 100;


    void updateTexts();

};

#endif