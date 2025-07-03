#include <soldier/PlayerSoldier.hpp>
#include <SFML/Window/Event.hpp>
#include <math.h>
#include <iostream>




void PlayerSoldier::handleInput(const sf::Event& event) {

    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
        if (getSoldierWeapon()) {
            getSoldierWeapon()->reload();
        }
    }

     // Shoot with left mouse button
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F) {
        
    }

}

void PlayerSoldier::update(float dt) {
    float speed = 200.0f;

    sf::Vector2f movement(0.f,0.f);
    
    if(getSoldierWeapon()) {
        getSoldierWeapon()->update(dt);
    }

    // Move with WASD
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += 1.f;

    // Normalize for diagonal movement
    if (movement.x != 0.f || movement.y != 0.f) {
        float len = std::sqrt(movement.x * movement.x + movement.y * movement.y);
        movement /= len;
    }

    moveSoldierBy(movement * speed * dt);

    if (windowRef) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*windowRef);
        sf::Vector2f worldMouse = windowRef->mapPixelToCoords(mousePos);

        sf::Vector2f dir = worldMouse - getSoldierPosition();
        float angle = std::atan2(dir.y, dir.x) * 180.f / 3.14159265f;

        setSoldierRotation(angle + 15.f);
    }

}

std::unique_ptr<BaseProjectile> PlayerSoldier::shootWeapon(const sf::Vector2f& targetPos) {
    if (!getSoldierWeapon()) return nullptr;
    if (!getCurrentHealth() > 0) return nullptr;
    sf::Vector2f spawnPos = getSoldierPosition();

    sf::Vector2f target = targetPos;
    sf::Vector2f dir = target - spawnPos;
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len != 0)
        dir /= len;


    // std::cout << "Player Pos: " << spawnPos.x << ", " << spawnPos.y << "\n";
    // std::cout << "Target Pos: " << target.x << ", " << target.y << "\n";
    // std::cout << "Dir: " << dir.x << ", " << dir.y << "\n";
    
    return getSoldierWeapon()->shoot(spawnPos, dir, getEffectiveAccuracy());

}