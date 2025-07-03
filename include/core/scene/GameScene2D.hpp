#ifndef GAMESCENE2D_HPP
#define GAMESCENE2D_HPP

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

#include <nav/NavMesh.hpp>
#include <soldier/PlayerSoldier.hpp>
#include <soldier/AISoldier.hpp>
#include <renderer/SoldierRenderer.hpp>
#include <renderer/ProjectileRenderer.hpp>
#include <projectile/BaseProjectile.hpp>
#include <ui/Hud.hpp>
#include <config/GameConfig.hpp>




class GameScene2D {
public:
    GameScene2D(sf::Vector2u windowSize, const GameConfig& config);
    void handleEvents(sf::RenderWindow& window);
    void update(float dt);
    void render(sf::RenderWindow& window);


private:
    ProjectileRenderer projectileRenderer;
    SoldierRenderer soldierRenderer;
    std::vector<std::unique_ptr<BaseProjectile>> projectiles;
    std::vector<std::unique_ptr<AISoldier>> enemies;
    std::unique_ptr<PlayerSoldier> playerSoldier;
    BaseWeapon* playerWeapon = nullptr;
    Hud hud;
    sf::Sprite player;
    sf::Texture PlayerTexture;
    sf::View view;
    bool initalizedPlayerWindowRef = false;
    NavMesh navMesh;
    const GameConfig& config;

};



#endif