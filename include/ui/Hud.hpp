#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>

class Hud {
public:
    Hud();
    
    void update(int ammo , int health);
    void render(sf::RenderWindow& window);

    void setHealth(int hp);
    void setAmmo(int current, int max);

private:
    sf::Font font;
    sf::Text ammoText;
    sf::Text healthText;

    int health = 100;
    int currentAmmo = 30;
    int maxAmmo = 30;


    void updateTexts();

};

#endif