#include <renderer/ProjectileRenderer.hpp>
#include <soldier/BaseSoldier.hpp>

ProjectileRenderer::ProjectileRenderer() {}

void ProjectileRenderer::render(sf::RenderWindow& window, const BaseProjectile& projectile) {
    float rad = 2.f;

    //Default color
    sf::Color bulletColor = sf::Color::White;
    const BaseSoldier* owner = projectile.getOwner();

    if (owner) {
        if(owner->isPlayer()) {
            bulletColor = sf::Color::Blue;
        }
        else {
            bulletColor = sf::Color::Red; //AI
        }
    } else {
        bulletColor = sf::Color(128, 128, 128); // Unknown/neutral
    }

    sf::CircleShape shape(rad);
    shape.setFillColor(bulletColor);
    shape.setOrigin(rad,rad);
    shape.setPosition(projectile.getPosition());
    window.draw(shape);
}