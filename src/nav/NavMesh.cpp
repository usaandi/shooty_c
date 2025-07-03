#include <nav/NavMesh.hpp>
#include <fstream>
#include <sstream>
#include <limits>


NavMesh::NavMesh(){}
NavMesh::~NavMesh(){}

bool NavMesh::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open navmesh file: " << filename << std::endl;
        return false;
    }
    nodes.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#')continue;
        std::istringstream iss(line);
        float x, y;
        iss >> x >> y;
        NavMeshNode node;
        node.position = {x, y};
        int neighbor;
        while (iss >> neighbor) {
            node.neighbors.push_back(neighbor);
        }
        nodes.push_back(node);
    }
    return true;
}

int NavMesh::getClosestNode(const sf::Vector2f& pos) const {
    int closest = -1;
    float minDist = std::numeric_limits<float>::max();
    for (size_t i = 0; i < nodes.size(); ++i) {
        float dx = nodes[i].position.x - pos.x;
        float dy = nodes[i].position.y - pos.y;
        float dist = dx * dx + dy * dy;
        if (dist < minDist) {
            minDist = dist;
            closest = static_cast<int>(i);
        }
    }
    return closest;
}
