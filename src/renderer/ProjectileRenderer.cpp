#include <renderer/ProjectileRenderer.hpp>

ProjectileRenderer::ProjectileRenderer() {}

void ProjectileRenderer::render(sf::RenderWindow& window, const BaseProjectile& projectile) {
    float rad = 2.f;
    sf::CircleShape shape(rad);
    shape.setFillColor(sf::Color::Black);
    shape.setOrigin(rad,rad);
    shape.setPosition(projectile.getPosition());
    window.draw(shape);
}