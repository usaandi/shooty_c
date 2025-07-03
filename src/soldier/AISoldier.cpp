#include <soldier/AISoldier.hpp>
#include <config/SoldierTypeConfig.hpp>
#include <nav/PathFinding.hpp>
#include <string>
#include <math.h>
#include <iostream>

static int enemyCount = 0;

AISoldier::AISoldier(const sf::Vector2f& pos) 
    : BaseSoldier("Enemy" + std::to_string(++enemyCount), config::SoldierType::INFANTRY)

{
    setSoldierPosition(pos);
    pickRandomPatrolTarget();
}

std::unique_ptr<BaseProjectile> AISoldier::update(float dt, const BaseSoldier& target, const std::vector<std::unique_ptr<AISoldier>>& allEnemies) { 
    sf::Vector2f toPlayer = target.getSoldierPosition() - getSoldierPosition();
    bool seesPlayer = canSeePlayer(target.getSoldierPosition());
    switch (state) {
        case AIState::Patrol:
            updatePatrol(dt);
            if (seesPlayer) {
                state = AIState::Chase;
            }
            break;
        case AIState::Chase:
            return updateChase(dt, target, allEnemies);
            if (!seesPlayer) {
                state = AIState::Patrol;
            }
            break;
    }

 
    // float distance = std::sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);
    // if (distance > 100.f) { // Only move if far away
    //     sf::Vector2f dir = toPlayer / distance;
    //     moveSoldierBy(dir * 50.f * dt);
    // }
    
    
    return nullptr;

}

void AISoldier::update(float dt) {
    //Basic AI
}
bool AISoldier::isFriendlyInLineOfFire(const sf::Vector2f targetPos, const std::vector<std::unique_ptr<AISoldier>>& allEnemies) const 
{
    sf::Vector2f myPos = getSoldierPosition();
    sf::Vector2f toTarget = targetPos - myPos;

    //Euclidean distance from the origin
    float targetDist = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y);

    for (const auto& other : allEnemies) {
        if (other.get() == this || !other->isAlive()) continue;
        sf::Vector2f otherPos = other->getSoldierPosition();

        // Project otherPos onto the line from myPos to targetPos
        sf::Vector2f toOther = otherPos - myPos;
        float proj = (toOther.x * toTarget.x + toOther.y * toTarget.y) / targetDist;
        if ( proj < 0 || proj > targetDist) continue; //not between

        sf::Vector2f closest = myPos + (toTarget / targetDist ) * proj;
        float distanceToLine = std::hypot(otherPos.x - closest.x, otherPos.y - closest.y);

        if (distanceToLine < 20.f) {
            return true;
        }
    }
    return false;
}
bool AISoldier::canSeePlayer(const sf::Vector2f& playerPos) const 
{
    sf::Vector2f toPlayer = playerPos - getSoldierPosition();
    float distance = std::sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);
    if (distance < 100.f)
        return false;
    
    //Direction AI is facing right now.
    sf::Vector2f forward = getForwardVector();
    float dot = (toPlayer.x * forward.x + toPlayer.y * forward.y) / (distance * std::sqrt(forward.x * forward.x + forward.y * forward.y));
    float angle = std::acos(dot) * 180.f / 3.14159f;
    return angle < 45.f; // 90 degree cone

}

sf::Vector2f AISoldier::getForwardVector() const 
{
    float rad = getSoldierRotation() * 3.141f / 180.f;
    return sf::Vector2f(std::cos(rad), std::sin(rad));
}

std::unique_ptr<BaseProjectile> AISoldier::updateChase(float dt, const BaseSoldier& target, const std::vector<std::unique_ptr<AISoldier>>& enemies) 
{
    sf::Vector2f toPlayer = target.getSoldierPosition() - getSoldierPosition();
    if (navMesh) {
        float angle = std::atan2(toPlayer.y, toPlayer.x) * 180.f / 3.14f;
        setSoldierRotation(angle);

        int startNode = navMesh->getClosestNode(getSoldierPosition());
        int goalNode = navMesh->getClosestNode(target.getSoldierPosition());
        PathFinding pf;
        std::vector<int> path = pf.findPathBFS(*navMesh, startNode, goalNode);

        if (path.size() > 1) {
            // Move toard th enext node in the path
            sf::Vector2f nextTarget = navMesh->getNodes()[path[1]].position;
            sf::Vector2f toNext = nextTarget - getSoldierPosition();
            float distance = std::sqrt(toNext.x * toNext.x + toNext.y * toNext.y);
            if(distance > 1.f) {
                sf::Vector2f dir = toNext / distance;
                moveSoldierBy(dir * 50.f * dt);

            }
        }
    }

    //Ran out of bullets need to reload
    if(getSoldierWeapon() && getSoldierWeapon()->getAmmo() == 0) {
        getSoldierWeapon()->reload();
    }

    if (getSoldierWeapon()) {
        if (!isFriendlyInLineOfFire(target.getSoldierPosition(), enemies) && target.isAlive()) {
            sf::Vector2f dir = target.getSoldierPosition() - getSoldierPosition();
            float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            if (len != 0)
                dir /= len;
            else
                dir = {1.f, 0.f}; // fallback
            
            auto proj = getSoldierWeapon()->shoot(getSoldierPosition(), dir, getEffectiveAccuracy());
        
            return proj; // Return the projectile to the scene
        }
    }

    return nullptr;
}

void AISoldier::updatePatrol(float dt) 
{
    if (patrolTargetNode == -1 || !navMesh) {
        pickRandomPatrolTarget();
    }
    while (true) {
        sf::Vector2f patrolPos = navMesh->getNodes()[patrolTargetNode].position;
        sf::Vector2f toPatrol = patrolPos - getSoldierPosition();
        float distance = std::sqrt(toPatrol.x * toPatrol.x + toPatrol.y * toPatrol.y);


        if (distance < 25.f) { // Arrived at patrol point
            pickRandomPatrolTarget();
            continue;
        }

        int startNode = navMesh->getClosestNode(getSoldierPosition());
        PathFinding pf;
        std::vector<int> path = pf.findPathBFS(*navMesh, startNode, patrolTargetNode);    


        if (path.size() <= 1) {
            std::cout << "No valid path, picking new patrol target." << std::endl;
            pickRandomPatrolTarget();
            continue;
        }


        if (path.size() > 1) {
            sf::Vector2f nextTarget = navMesh->getNodes()[path[1]].position;
            sf::Vector2f toNext = nextTarget - getSoldierPosition();
            float nextDist = std::sqrt(toNext.x * toNext.x + toNext.y * toNext.y);
            if (nextDist > 1.f) {
                float angle = std::atan2(toNext.y, toNext.x) * 180.f / 3.141f;
                setSoldierRotation(angle);
                sf::Vector2f dir = toNext / nextDist;
                moveSoldierBy(dir * 100.f * dt);
            }
        }
        break;
    }
   

}

void AISoldier::pickRandomPatrolTarget() {
    if (navMesh && !navMesh->getNodes().empty()) {
        int newTarget;
        do {
            newTarget = rand () % navMesh->getNodes().size();
        } while (navMesh->getNodes().size() > 1 && newTarget == patrolTargetNode);
        patrolTargetNode = newTarget;
    }
}