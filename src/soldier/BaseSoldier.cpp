#include <cstdlib>
#include <iostream>

#include <soldier/BaseSoldier.hpp>
#include <soldier/SoldierType.hpp>

#include <config/SoldierTypeConfig.hpp>
#include <weapon/factory/WeaponFactory.hpp>



BaseSoldier::BaseSoldier(
        const std::string &name, config::SoldierType soldierType) 
        : name(name), soldierType(soldierType), soldierPosition(300.0f, 400.0f)
        

{
    auto it = config::SOLDIER_TYPE_CONFIG.find(soldierType);
    if (it == config::SOLDIER_TYPE_CONFIG.end()) {
        throw std::runtime_error("Invalid SoldierType passed to BaseSoldier constructor");
    }
    soldierStats = it->second.defaultStats;
    currentHealth = soldierStats.maxHealth;

    const auto& allowedWeaponTypes = it->second.allowedWeaponClasses;

    if (!allowedWeaponTypes.empty()) {
        WeaponType chosenType = WeaponFactory::getRandomWeaponTypeFromSet(allowedWeaponTypes);
        soldierWeapon = WeaponFactory::createRandomWeaponFromType(chosenType);
    }
}



BaseSoldier::~BaseSoldier(){}

BaseWeapon* BaseSoldier::getSoldierWeapon() const
{
    return soldierWeapon.get();
}


const std::string &BaseSoldier::getSoldierName() const
{
    return name;
}

config::SoldierType BaseSoldier::getSoldierType() const 
{
    return soldierType;
}

const SoldierStats &BaseSoldier::getSoldierStats() const 
{
    return soldierStats;
}
void BaseSoldier::shootWeapon() 
{
    if(soldierWeapon) {
        soldierWeapon->shoot();
    } else {
        std::cout << name << " has no weapon!" << std::endl;
    }
}

int BaseSoldier::getCurrentHealth() const 
{
    return currentHealth;
}

void BaseSoldier::damageCurrentHealth(int amount) 
{
    std::cout << std::to_string(currentHealth) << "\n";
    currentHealth -= amount;
    if(currentHealth < 0) currentHealth = 0;
}

float BaseSoldier::getEffectiveAccuracy() const {
    return 0.5f * (1.0f - soldierStats.fatigue * 0.5f);
}

const sf::Vector2f& BaseSoldier::getSoldierPosition() const
{
    return soldierPosition;
}

sf::Vector2f& BaseSoldier::getSoldierPosition() 
{
    return soldierPosition;
}

void BaseSoldier::setSoldierPosition(const sf::Vector2f& newPos) 
{
    soldierPosition = newPos;
}
void BaseSoldier::moveSoldierBy(const sf::Vector2f& delta)
{
    soldierPosition += delta;
}

void BaseSoldier::setSoldierRotation(float angle) {
    soldierRotation = angle;
}

float BaseSoldier::getSoldierRotation() const {
    return soldierRotation;
}


void BaseSoldier::update(float dt) {
    // Base behavior or empty
}

bool BaseSoldier::isAlive() const {
    return getCurrentHealth() > 0;
}
sf::FloatRect BaseSoldier::getBounds() const {
    //Sprite size is currently 50,50
    float size = 50.f;
    sf::Vector2f pos = getSoldierPosition();
    return sf::FloatRect(pos.x - size / 2.f, pos.y -size/2.f,size,size);
}