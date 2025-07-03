#ifndef PROJECTILERENDERER_HPP
#define PROJECTILERENDERER_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <projectile/BaseProjectile.hpp>


class ProjectileRenderer {


public:
    ProjectileRenderer();
    void render(sf::RenderWindow& window, const BaseProjectile& projectile);
};

#endif // PROJECTILERENDERER_HPP