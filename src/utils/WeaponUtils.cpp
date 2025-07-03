#include <utils/WeaponUtils.hpp>
#include <vector>
#include <random>
#include <stdexcept>


WeaponType getRandomWeaponType(const std::unordered_set<WeaponType>& allowedWeaponTypes) {
    if (allowedWeaponTypes.empty()) {
        throw std::runtime_error("No allowed weapon types to choose from.");
    }


    std::vector<WeaponType> typesVec(allowedWeaponTypes.begin(), allowedWeaponTypes.end());

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0,typesVec.size() - 1);


    return typesVec[distrib(gen)];
}