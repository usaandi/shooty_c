#ifndef NAVMESH_HPP
#define NAVMESH_HPP

#include <vector>
#include <SFML/System/Vector2.hpp>
#include <iostream>

struct NavMeshNode {
    sf::Vector2f position;
    std::vector<int> neighbors;
};

class NavMesh {
public:
    NavMesh();
    ~NavMesh();
    bool loadFromFile(const std::string& filename);
    int getClosestNode(const sf::Vector2f& pos) const;
    const std::vector<NavMeshNode>& getNodes() const { return nodes; }

private:
    std::vector<NavMeshNode> nodes;

};

#endif