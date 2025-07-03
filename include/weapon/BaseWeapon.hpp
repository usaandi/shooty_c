#ifndef BASEWEAPON_HPP
#define BASEWEAPON_HPP

#include <string>
#include <cstdint>
#include <memory>
#include "WeaponType.hpp"
#include <projectile/BaseProjectile.hpp>



class BaseWeapon {
      
public:
    BaseWeapon(
        const std::string& weaponName, 
        float weaponDamage, 
        float weaponEaseOfUse, 
        float weaponReliability,
        float weaponWeight,
        float weaponBaseAccuracy,
        float weaponReloadSpeed,
        uint8_t weaponMagazineSize,
        uint8_t weaponCurrentBullet,
        int weaponEffectiveRange,
        WeaponType weaponType,
        float shootInterval
    );

    virtual ~BaseWeapon();
    void reload();
    void shoot(); 
    void update(float dt);
    uint8_t getAmmo() const;
    uint8_t getMaxAmmo() const;
    virtual std::unique_ptr<BaseProjectile> shoot(const sf::Vector2f& spawnPos, const sf::Vector2f& direction);
    virtual std::unique_ptr<BaseProjectile> shoot(const sf::Vector2f& spawnPos, const sf::Vector2f& direction, float soldierAccuracy);
    float getWeaponDamage();
    const std::string& getWeaponName() const;

    WeaponType getWeaponType() const;
    std::string getWeaponTypeName() const;
    bool canFire() const;
    sf::Vector2f applySpread(const sf::Vector2f& dir, float accuracy);

private:
    std::string weaponName;
    float weaponDamage;
    float weaponEaseOfUse; //between 0-1 
    float weaponReliability; // Between 0-1 0.75f = 75%
    float weaponWeight;
    float weaponBaseAccuracy;
    float weaponReloadSpeed;
    uint8_t weaponMagazineSize;
    uint8_t weaponCurrentBullet;
    int weaponEffectiveRange;
    WeaponType weaponType;
    float shootInterval;
    BaseWeapon();
    float timeSinceLastShot = 0.f;

    };

    #endif