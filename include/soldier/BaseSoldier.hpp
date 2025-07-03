#ifndef BASESOLDIER_HPP
#define BASESOLDIER_HPP

#include <memory>
#include <string>

#include <soldier/SoldierStats.hpp>
#include <soldier/SoldierType.hpp>
#include <weapon/BaseWeapon.hpp>




class BaseSoldier {
public:
    BaseSoldier(const std::string& name, config::SoldierType soldierType);
    virtual ~BaseSoldier();
   
    BaseWeapon* getSoldierWeapon() const;
    const std::string& getSoldierName() const;
    const SoldierStats& getSoldierStats() const;
    sf::FloatRect getBounds() const;
    const sf::Vector2f& getSoldierPosition() const;
    sf::Vector2f& getSoldierPosition();
    config::SoldierType getSoldierType() const;

    int getCurrentHealth() const;
    float getEffectiveAccuracy() const;
    float getSoldierRotation() const;

    void setSoldierPosition(const sf::Vector2f& newPos);
    void setSoldierRotation(float angle);
    void moveSoldierBy(const sf::Vector2f& delta);
    void damageCurrentHealth(int amount);
    void shootWeapon();
    bool isAlive() const;
    virtual void update(float dt) = 0;
    virtual bool isPlayer() const { return false; }

private:
    std::string name;
    config::SoldierType soldierType;
    SoldierStats soldierStats;
    std::unique_ptr<BaseWeapon> soldierWeapon;
    int currentHealth;
    sf::Vector2f soldierPosition;
    float soldierRotation;

};

void logMessage(const  std::string& message);

#endif // BASESOLDIER_HPP