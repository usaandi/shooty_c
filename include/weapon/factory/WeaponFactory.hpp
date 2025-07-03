#ifndef WEAPONFACTORY_HPP
#define WEAPONFACTORY_HPP

#include <weapon/BaseWeapon.hpp>
#include <weapon/WeaponType.hpp>

#include <memory>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>


class WeaponFactory {
    public:
    static void registerWeapons(); // Need to call on startup or initalize when called
    static std::unique_ptr<BaseWeapon> createRandomWeaponFromType(WeaponType weaponType);
    static WeaponType getRandomWeaponTypeFromSet(const std::unordered_set<WeaponType>& allowedTypes);

    private:
        static std::unordered_map<WeaponType, std::vector<std::function<std::unique_ptr<BaseWeapon>()>>> weaponMap;
};


#endif