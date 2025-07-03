#include <config/SoldierTypeConfig.hpp>
#include <random>
#include <SFML/Graphics.hpp>


namespace config {


    const std::unordered_map<SoldierType, SoldierTypeConfig> SOLDIER_TYPE_CONFIG = {
        { 

            SoldierType::INFANTRY,
            {
                /*Order maxHealth, morale, flatArmor, fatigue, experience*/
                {125.f, 1.0f, 1.0f ,1.0f , 0},
                {WeaponType::ASSAULT_RIFLE}
            }
        },
        {
            SoldierType::HEAVY,
            {
                /*Order maxHealth, morale, flatArmor, fatigue, experience*/
                {200.0f, 1.0f, 1.0f ,1.0f , 0},
                {WeaponType::LIGHT_MACHINE_GUN}
            }
        }
    };

}