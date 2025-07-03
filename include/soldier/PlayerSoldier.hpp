#ifndef PLAYERSOLDIER_HPP
#define PLAYERSOLDIER_HPP

#include <soldier/BaseSoldier.hpp>
#include <projectile/BaseProjectile.hpp>
#include <SFML/Graphics.hpp>

class PlayerSoldier : public BaseSoldier {
public:
    using BaseSoldier::BaseSoldier;
    void handleInput(const sf::Event& event);
    void update(float dt) override;
    void setWindow(sf::RenderWindow* win) {windowRef = win;}
    std::unique_ptr<BaseProjectile> shootWeapon(const sf::Vector2f& targetPos);
    bool isPlayer() const override { return true; }
private:
    sf::RenderWindow* windowRef = nullptr;
};

#endif