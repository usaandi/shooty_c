#ifndef WEAPONUTILS_HPP
#define WEAPONUTILS_HPP

#include <weapon/WeaponType.hpp>
#include <unordered_set>

WeaponType getRandomWeaponType(const std::unordered_set<WeaponType>& allowedWeaponTypes);



#endif