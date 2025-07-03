#include <weapon/factory/WeaponFactory.hpp>
#include <weapon/assault_rifle/M16.hpp>

#include <random>
#include <stdexcept>

std::unordered_map<WeaponType, std::vector<std::function<std::unique_ptr<BaseWeapon>()>>> WeaponFactory::weaponMap;

void WeaponFactory::registerWeapons() {
    weaponMap[WeaponType::ASSAULT_RIFLE] = {
        [](){ return std::make_unique<M16>(); },
    };



    // Add more for other WeaponTypes make sure to call it otherwise will throw error.
}


std::unique_ptr<BaseWeapon> WeaponFactory::createRandomWeaponFromType(WeaponType type) {
    const auto& list = weaponMap.at(type);

    if (list.empty()) throw std::runtime_error("No weapons registered for this type");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, list.size() - 1);

    return list[dist(gen)]();
}

WeaponType WeaponFactory::getRandomWeaponTypeFromSet(const std::unordered_set<WeaponType>& weaponTypes) {
    if (weaponTypes.empty()) {
        throw std::runtime_error("WeaponType set is empty");
    }

    // Convert unordered_set to vector for indexing
    std::vector<WeaponType> vec(weaponTypes.begin(), weaponTypes.end());

    // Random engine (seed with random device for example)
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist(0, vec.size() - 1);
    return vec[dist(gen)];
}



namespace {
    struct WeaponInitializer {
        WeaponInitializer() {
            WeaponFactory::registerWeapons();
        }
    };

    static WeaponInitializer _weaponInitializer;
}