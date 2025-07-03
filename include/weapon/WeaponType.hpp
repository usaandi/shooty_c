#ifndef WEAPONTYPE_HPP
#define WEAPONTYPE_HPP
#include <string>

enum class WeaponType {
    ASSAULT_RIFLE,
    SNIPER_RIFLE,
    LIGHT_MACHINE_GUN,
    SUBMACHINE_GUN
};


/* Functions needs to be inline in the header to avoid linker issues */
inline std::string to_string(WeaponType type) {
    switch (type) {
        case WeaponType::ASSAULT_RIFLE: return "ASSAULT_RIFLE";
        case WeaponType::SNIPER_RIFLE: return "SNIPER_RIFLE";
        case WeaponType::LIGHT_MACHINE_GUN: return "LIGHT_MACHINE_GUN";
        case WeaponType::SUBMACHINE_GUN: return "SUBMACHINE_GUN";
        default: return "UNKNOWN";
    }
}



#endif