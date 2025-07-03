#ifndef AISOLDIER_HPP
#define AISOLDIER_HPP

#include <soldier/BaseSoldier.hpp>
#include <projectile/BaseProjectile.hpp>
#include <SFML/System/Vector2.hpp>
#include <nav/NavMesh.hpp>

enum class AIState { Patrol, Chase };


class AISoldier : public BaseSoldier {
private:
    const NavMesh* navMesh = nullptr;
    AIState state = AIState::Patrol;
    int patrolTargetNode = -1;
public:
    explicit AISoldier(const sf::Vector2f& pos);
    void update(float dt) override;
    std::unique_ptr<BaseProjectile> update(float dt, const BaseSoldier& target, const std::vector<std::unique_ptr<AISoldier>>& allEnemies);
    void updatePatrol(float dt);
    std::unique_ptr<BaseProjectile> updateChase(float dt, const BaseSoldier& target, const std::vector<std::unique_ptr<AISoldier>>& enemies);
    bool isFriendlyInLineOfFire(const sf::Vector2f targetPos, const std::vector<std::unique_ptr<AISoldier>>& allEnemies) const;
    void setNavMesh(const NavMesh* mesh) { navMesh = mesh;}
    bool canSeePlayer(const sf::Vector2f& playerPos) const;
    sf::Vector2f getForwardVector() const;
    void pickRandomPatrolTarget();
};

#endif