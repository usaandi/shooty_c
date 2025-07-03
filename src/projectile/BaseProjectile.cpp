#include <projectile/BaseProjectile.hpp>
#include <cmath>
#include <soldier/BaseSoldier.hpp>

BaseProjectile::BaseProjectile( const sf::Vector2f& position, const sf::Vector2f& velocity, float maxRange) 
    : position(position), velocity(velocity), maxRange(maxRange) {}


void BaseProjectile::update(float dt) {
    if (!isActive()) return;

    sf::Vector2f displacement = velocity * dt;
    position += displacement;

    traveledDistance += std::sqrt(displacement.x * displacement.x + displacement.y * displacement.y);
    if (traveledDistance >= maxRange) {
        active = false;
    }

}

const sf::Vector2f& BaseProjectile::getPosition() const {
    return position;
}

const sf::Vector2f& BaseProjectile::getVelocity() const {
    return velocity;
}


bool BaseProjectile::isActive() const {return active;}

sf::FloatRect BaseProjectile::getBounds() const {
    float size = 2.f; //Current projectile radius. Need to refactor later
    return sf::FloatRect(position.x - size / 2.f, position.y - size / 2.f, size, size);
}
void BaseProjectile::deactivate() {
    active = false;
}
