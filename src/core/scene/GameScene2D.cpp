#include <core/scene/GameScene2D.hpp>
#include <config/GameConfig.hpp>
#include <renderer/ProjectileRenderer.hpp>
#include <renderer/SoldierRenderer.hpp>
#include <soldier/PlayerSoldier.hpp>
#include <soldier/AISoldier.hpp>
#include <nav/PathFinding.hpp>
#include <ui/Hud.hpp>
#include <cmath>
#include <iostream>

GameScene2D::GameScene2D(sf::Vector2u windowSize, const GameConfig& config) 
    : config(config)
{
    SoldierRenderer soldierRenderer;
    ProjectileRenderer projectileRenderer;
    Hud hud;
    view.setSize(static_cast<sf::Vector2f>(windowSize));
    view.setCenter(view.getSize() / 2.f);
    playerSoldier = std::make_unique<PlayerSoldier>("Player1", config::SoldierType::INFANTRY);
    auto ai1 = std::make_unique<AISoldier>(sf::Vector2f{200.f, 100.f});
    ai1->setNavMesh(&navMesh);
    enemies.push_back(std::move(ai1));
    playerWeapon = playerSoldier->getSoldierWeapon();
    //NOT MOST ELEGANT SOLUTION
    navMesh.loadFromFile("../assets/navmesh/navmesh.txt");
    
}


void GameScene2D::handleEvents(sf::RenderWindow& window) {
    if(!initalizedPlayerWindowRef && playerSoldier) {
        playerSoldier->setWindow(&window);
        initalizedPlayerWindowRef = true;
    }
    // handle player input
    sf::Event event;

    window.setView(view);
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::Resized) {
            view.setSize(static_cast<float>(event.size.width), static_cast<float>(event.size.height));

        }
    }
    
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2f target = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        
        if(playerSoldier) {
            auto proj = playerSoldier->shootWeapon(target);
            if (proj)  {
                proj->setOwner(playerSoldier.get());
                projectiles.push_back(std::move(proj)); }
        }
    }


    if (playerSoldier) {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F) {
            sf::Vector2f spawnPos{100.f + static_cast<float>(rand() % 500), 100.f + static_cast<float>(rand() % 500)};
            auto aiSoldier = std::make_unique<AISoldier>(spawnPos);
            aiSoldier->setNavMesh(&navMesh);
            enemies.push_back(std::move(aiSoldier));
        }

        playerSoldier->handleInput(event);
    }

}

void GameScene2D::update(float dt) {

    //Player update
    if (playerSoldier) {
        BaseWeapon* weapon = playerSoldier->getSoldierWeapon();
        int healty = playerSoldier->getCurrentHealth();
        float maxHealth = playerSoldier->getSoldierStats().maxHealth;
        hud.setHealth(healty, maxHealth);
        int currentAmmo = weapon->getAmmo();
        int maxAmmo = weapon->getMaxAmmo();

        hud.setAmmo(currentAmmo,maxAmmo);
        hud.update(currentAmmo,healty);

        playerSoldier->update(dt);
    }


    //Projectiles update
    for (auto& projectile : projectiles) {
        projectile->update(dt);
    }
    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
        [](const std::unique_ptr<BaseProjectile>& proj) {
            return !proj->isActive();
        }),
        projectiles.end()
    );


    for(auto& enemy : enemies) {

        //Check weapon and update
        if (enemy->getSoldierWeapon()) {
            enemy->getSoldierWeapon()->update(dt);
        }
        //Projectile when enemy shoots.
        auto proj = enemy->update(dt, *playerSoldier, enemies);
        if (proj) {
            proj->setOwner(enemy.get());
            projectiles.push_back(std::move(proj));
        } 
    }

    //CHECK bullet COLLISION WITH ENEMY
    for (auto& projectile : projectiles) {
        if (!projectile->isActive()) continue;

        for (auto& enemy : enemies) {
            if (!enemy->isAlive()) continue;
            if (projectile->getOwner() == enemy.get()) continue;
            if (projectile->getBounds().intersects(enemy->getBounds())) {
                if(enemy->getSoldierWeapon()) {
                    std::cout << enemy->getSoldierName() << std::endl;
                    enemy->damageCurrentHealth(playerWeapon->getWeaponDamage());
                    projectile->deactivate();
                }
                break;
            }
        }
    }

    // Check if player is hit by any projectile
    if (playerSoldier) {
        for (auto& projectile : projectiles) {
            if (!projectile->isActive()) continue;
            // Don't let player be hit by their own bullets
            if (projectile->getOwner() == playerSoldier.get()) continue;
            if (projectile->getBounds().intersects(playerSoldier->getBounds())) {

                const BaseSoldier* owner = projectile->getOwner();
                int damage = 10; // default
                if (owner && owner->getSoldierWeapon()) {
                    damage = owner->getSoldierWeapon()->getWeaponDamage();
                }
                playerSoldier->damageCurrentHealth(damage);
                projectile->deactivate();
                break; // Only one hit per projectile
            }
        }
    }



    int deadCount = 0;
    for (const auto& enemy : enemies) {
        if (!enemy->isAlive()) deadCount++;

    }
    //Remove dead enemies
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
        [](const std::unique_ptr<AISoldier>& enemy){
            return !enemy->isAlive();
        }),
        enemies.end()
    );
    // Spawn new enemies for each dead one
    for (int i = 0; i < deadCount; ++i) {
        // Can randomize the spawn position if needed
       // sf::Vector2f spawnPos{100.f + static_cast<float>(rand() % 500), 100.f + static_cast<float>(rand() % 500)};
       // enemies.push_back(std::make_unique<AISoldier>(spawnPos));
    }
}

void GameScene2D::render(sf::RenderWindow& window) {

    if (playerSoldier) {
        sf::Vector2f pos = playerSoldier->getSoldierPosition();

        // Calculate half view size for clamping
        sf::Vector2f halfSize = view.getSize() / 2.f;

        // World bounds (hardcoded for now, can later be level-specific)
        const float worldWidth = config.worldWidth;
        const float worldHeight = config.worldHeight;

        // Clamp so view doesn't go out of bounds
        pos.x = std::clamp(pos.x, halfSize.x, worldWidth - halfSize.x);
        pos.y = std::clamp(pos.y, halfSize.y, worldHeight - halfSize.y);

        sf::Vector2f currentCenter = view.getCenter();
        sf::Vector2f targetCenter = pos;
        float lerpFactor = .5f; // 0.0 = no movement, 1.0 = instant snap
        sf::Vector2f newCenter = currentCenter + (targetCenter - currentCenter) * lerpFactor;
        view.setCenter(newCenter);
        // Center view on player
    }
    window.setView(view);

    for(auto& enemy : enemies) {
        soldierRenderer.render(window, *enemy);
    }
    

    //Render player
    if(playerSoldier) {
        soldierRenderer.render(window, *playerSoldier);
        hud.renderPlayerHealthBar(window, playerSoldier->getSoldierPosition());
    }

    //Render projectiles
    for (auto& projectile : projectiles) {
        projectileRenderer.render(window, *projectile);
    }
    
    //Hud render
    window.setView(window.getDefaultView());
    hud.renderStatic(window);
    //soldierRenderer.render(window);
}