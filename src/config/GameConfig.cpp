#include <config/GameConfig.hpp>
#include <fstream>
#include <sstream>
#include <unordered_map>

bool GameConfig::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;
    std::unordered_map<std::string, std::string> kv;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        if (std::getline(iss, key, '=')) {
            std::string valueStr;
            if(std::getline(iss, valueStr)) {
                kv[key] = valueStr;
            }
        }
    }
        //Assign to struct, converting as needed
    if (kv.count("world_width"))      worldWidth = std::stof(kv["world_width"]);
    if (kv.count("world_height"))     worldHeight = std::stof(kv["world_height"]);
    if (kv.count("client_size_width"))  clientWidth = std::stoi(kv["client_size_width"]);
    if (kv.count("client_size_height")) clientHeight = std::stoi(kv["client_size_height"]);


    return true;
}