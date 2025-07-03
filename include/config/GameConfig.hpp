#ifndef GAMECONFIG_HPP
#define GAMECONFIG_HPP
#include <string>
#include <unordered_map>

struct GameConfig
{
    /* data */
    float worldWidth = 3000.f;
    float worldHeight = 2000.f;
    int clientWidth = 800;
    int clientHeight = 600;

    bool loadFromFile(const std::string& filename);
};

#endif