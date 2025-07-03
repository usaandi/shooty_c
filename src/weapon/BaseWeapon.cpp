#include <weapon/BaseWeapon.hpp>
#include <weapon/WeaponType.hpp>
#include <projectile/BaseProjectile.hpp>
#include <iostream>
#include <memory>
#include <random>



BaseWeapon::BaseWeapon(
    const std::string &weaponName,
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
    float shootInterval)
    : weaponName(weaponName),
      weaponDamage(weaponDamage),
      weaponEaseOfUse(weaponEaseOfUse),
      weaponReliability(weaponReliability),
      weaponWeight(weaponWeight),
      weaponBaseAccuracy(weaponBaseAccuracy),
      weaponReloadSpeed(weaponReloadSpeed),
      weaponMagazineSize(weaponMagazineSize),
      weaponCurrentBullet(weaponMagazineSize),
      weaponEffectiveRange(weaponEffectiveRange),
      weaponType(weaponType),
      shootInterval(shootInterval)

{}

BaseWeapon::~BaseWeapon()
{
}

void BaseWeapon::reload()
{
    weaponCurrentBullet = weaponMagazineSize;
}


float BaseWeapon::getWeaponDamage()
{
    return weaponDamage;
}

const std::string& BaseWeapon::getWeaponName() const
{
    return weaponName;
}

WeaponType BaseWeapon::getWeaponType() const
{
    return weaponType;
}

std::string BaseWeapon::getWeaponTypeName() const 
{
    return to_string(weaponType);
}


bool BaseWeapon::canFire() const
{
    return weaponCurrentBullet > 0 && timeSinceLastShot >= shootInterval;
}

void BaseWeapon::shoot()
{
    if (!canFire()) {
        std::cout << "Cannot fire no bullets" << std::endl;
        return;
    }
    --weaponCurrentBullet;

    std::cout << std::to_string(weaponCurrentBullet) << std::endl;
} 

std::unique_ptr<BaseProjectile> BaseWeapon::shoot(const sf::Vector2f& spawnPos, const sf::Vector2f& direction) 
{
    if (!canFire()) return nullptr; //No ammo
    --weaponCurrentBullet;
    timeSinceLastShot = 0.f;
    float muzzleOffset = 20.f;
    sf::Vector2f muzzlePos = spawnPos + direction * muzzleOffset;
    sf::Vector2f velocity = direction * 300.f; // Or weapon-specific speed

    return std::make_unique<BaseProjectile>(muzzlePos, velocity, weaponEffectiveRange);

}

std::unique_ptr<BaseProjectile> BaseWeapon::shoot(const sf::Vector2f& spawnPos, const sf::Vector2f& rawDirection, float soldierAccuracy) 
{
    if (!canFire()) return nullptr; //No ammo
    --weaponCurrentBullet;
    timeSinceLastShot = 0.f;

    sf::Vector2f direction = applySpread(rawDirection, soldierAccuracy);

    // Gun barrel pixel coords in sprite space (top-left origin)
    sf::Vector2f barrelPixel(48.f, 18.f);

    // Define gun barrel offset in player local space (tweak these numbers) this needs to be fixed later on.
    sf::Vector2f gunBarrelOffset(
    barrelPixel.x - 50.0f / 2.f, 
    barrelPixel.y - 50.0f / 2.f + 7.f );
    // Calculate rotation angle from direction vector
    float angleRad = std::atan2(direction.y, direction.x);
    float cosA = std::cos(angleRad);
    float sinA = std::sin(angleRad);

    // Rotate offset vector by the angle
    sf::Vector2f rotatedOffset;
    rotatedOffset.x = gunBarrelOffset.x * cosA - gunBarrelOffset.y * sinA;
    rotatedOffset.y = gunBarrelOffset.x * sinA + gunBarrelOffset.y * cosA;

    // Calculate final muzzle spawn position with rotated offset
    sf::Vector2f muzzlePos = spawnPos + rotatedOffset;

    return std::make_unique<BaseProjectile>(muzzlePos, direction * 300.f, weaponEffectiveRange);

}



sf::Vector2f BaseWeapon::applySpread(const sf::Vector2f& dir , float accuracy) 
{
    static std::default_random_engine rng(std::random_device{}());


    // Angle deviation in radians, less accuracy = higher angle
    float maxAngle = (1.0f - accuracy) * 0.2f; // Up to ~11 degrees spread

    std::uniform_real_distribution<float> dist(-maxAngle, maxAngle);
    float angle = dist(rng);
    float cosA = std::cos(angle);
    float sinA = std::sin(angle);

    return {
        dir.x * cosA - dir.y * sinA,
        dir.x * sinA + dir.y *cosA
    };
}

uint8_t BaseWeapon::getAmmo() const
{
    return weaponCurrentBullet;
}

uint8_t BaseWeapon::getMaxAmmo() const
{
    return weaponMagazineSize;
}

void BaseWeapon::update(float dt) 
{
    if (timeSinceLastShot < shootInterval)
        timeSinceLastShot += dt;
}
/*
int BaseWeapon::getDamage() const
{
    return damage;
}





float BaseWeapon::getReloadTime() const
{
    return reloadTime;
}

float BaseWeapon::getFireRate() const
{
    return fireRate;
}

void BaseWeapon::setDamage(int dmg)
{
    damage = dmg;
}

void BaseWeapon::setAmmo(int a)
{
    ammo = a;
}

void BaseWeapon::setMaxAmmo(int maxA)
{
    maxAmmo = maxA;
}

void BaseWeapon::setReloadTime(float rt)
{
    reloadTime = rt;
}

void BaseWeapon::setFireRate(float fr)
{
    fireRate = fr;
}



*/