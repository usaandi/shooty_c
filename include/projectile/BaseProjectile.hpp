#ifndef BASEPROJECTILE_HPP
#define BASEPROJECTILE_HPP

#include <SFML/Graphics.hpp>

class BaseSoldier;

class BaseProjectile
{
private:
    
public:
    BaseProjectile(
        const sf::Vector2f& position,
        const sf::Vector2f& velocity,
        float maxRange
    );
    virtual ~BaseProjectile() = default;

    void update(float dt); // declare virtual if adding other projectile behaviors
    bool isActive() const;
    const sf::Vector2f& getPosition() const;
    const sf::Vector2f& getVelocity() const;
    sf::FloatRect getBounds() const;
    void deactivate();
    const BaseSoldier* getOwner() const { return owner; }
    void setOwner(const BaseSoldier* o) { owner = o; }

protected:
    sf::Vector2f position;
    sf::Vector2f velocity;
    float traveledDistance = 0.f;
    float maxRange;
    bool active = true;

    const BaseSoldier* owner = nullptr;
    // sf::Sprite sprite; later on
};



#endif