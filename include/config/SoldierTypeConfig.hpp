#ifndef SOLDIERTYPECONFIG_HPP
#define SOLDIERTYPECONFIG_HPP
#include <unordered_set>
#include <unordered_map>
#include <soldier/SoldierType.hpp>
#include <weapon/WeaponType.hpp>
#include <soldier/SoldierStats.hpp>


namespace config {

struct SoldierTypeConfig {
   SoldierStats defaultStats;
   std::unordered_set<WeaponType> allowedWeaponClasses;
};

extern const std::unordered_map<SoldierType, SoldierTypeConfig> SOLDIER_TYPE_CONFIG;

} // namespace config

#endif