#include <nav/NavMesh.hpp>
#include <nav/PathFinding.hpp>

#include <queue>
#include <unordered_map>
#include <vector>
#include <algorithm>

std::vector<int> PathFinding::findPathBFS(const NavMesh& mesh, int start, int goal) {
    std::queue<int> q;
    std::unordered_map<int, int> cameFrom;
    q.push(start);
    cameFrom[start] = -1;

    while (!q.empty()) {
        int current = q.front(); q.pop();
        if( current == goal) break;
        for (int neighbor : mesh.getNodes()[current].neighbors) {
            if (cameFrom.count(neighbor) == 0) {
                cameFrom[neighbor] = current;
                q.push(neighbor);
            }
        }
    }

    std::vector<int> path;
    if (cameFrom.count(goal) == 0) return path; // No path found
    for (int at = goal; at != -1; at = cameFrom[at])
        path.push_back(at);
    std::reverse(path.begin(), path.end());
    return path;

}