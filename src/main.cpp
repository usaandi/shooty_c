#include <iostream>
#include <filesystem>

#include "core/Game.hpp"

int main() {

    // Have to call for now to register the weapons to factory FIXED
    //WeaponFactory::registerWeapons();
    /*M16 destoryerRifle;
    // std::cout << __cplusplus << std::endl;
    // std::cout << "Hello, World!" << std::endl;
    BaseSoldier soldier1("Axel the greaterrr", config::SoldierType::INFANTRY);
    std::cout << "Soldier:" << soldier1.getSoldierName() << std::endl;
    std::cout <<"Soldier stats:" <<soldier1.getSoldierStats().currentHealth << "\n";
    

    BaseWeapon* weapon = soldier1.getSoldierWeapon();
    if(weapon) {
        std::cout << weapon->getWeaponName() << std::endl;
    }

    int x = 10;

    for (size_t i = 0; i < x; i++)
    {
         soldier1.shootWeapon();
    }*/
    
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    Game game;
    game.run();
    

    
    //std::cin.clear(); // reset any error flags
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore any characters in the input buffer until we find an enter character
    //std::cin.get(); 

   
    

    /*BaseWeapon testingWeapon(
        "BURSTER 3000",
        30.0f,
        1.0f,
        1.0f,
        30.0f,
        1.0f,
        3.0f,
        20,
        20,
        300,
        WeaponType::LIGHT_MACHINE_GUN
    );

    std::cout << "Weapon:" << destoryerRifle.getWeaponName() << std::endl;
    */
    /*
    std::cout << "Weapon: " << testingWeapon.getWeaponTypeName() << std::endl;
    std::cout << "Weapon damage:" << testingWeapon.getWeaponDamage() << std::endl;
    std::cout << "Weapon Name:" <<  testingWeapon.getWeaponName()  << std::endl;

    std::cout << "Weapon type (int): " << static_cast<int>(testingWeapon.getWeaponType()) << std::endl;
    */


}