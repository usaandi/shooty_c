#ifndef PATHFINDING_HPP
#define PATHFINDING_HPP

#include <vector>
#include <nav/NavMesh.hpp>

class PathFinding {
public:
    std::vector<int> findPathBFS(const NavMesh& mesh, int start, int goal);
    

};



#endif