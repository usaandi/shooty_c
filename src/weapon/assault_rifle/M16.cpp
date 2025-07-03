#include "weapon/assault_rifle/M16.hpp"


M16::M16()
    : BaseWeapon(
        "M16",
        10.f,    // damage
        0.8f,     // easeOfUse
        0.95f,    // reliability
        3.5f,     // weight
        0.9f,     // base accuracy
        2.0f,     // reload speed
        30,       // magazine size
        30,       // current bullets
        750,      // effective range
        WeaponType::ASSAULT_RIFLE,
        0.15f
    ) {}