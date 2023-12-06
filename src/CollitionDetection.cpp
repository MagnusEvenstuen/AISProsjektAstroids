#include "CollitionDetection.hpp"
#include "ObjectCreator.hpp"

bool CollitionDetection::collitionDestroy(std::shared_ptr<Astroid>& astroid, std::vector<Laser>& lasers) {
    //All collition Destroy functions are functions to destroy objects.
    for (auto is = lasers.begin(); is != lasers.end(); is++) {
        auto& laser = *is;

        const Vector3 laserPosition = laser.getPosition();
        const Vector3 astroidPosition = astroid -> getPosition();
        const float astroidSize = astroid -> getObjectSize();

        const float distance = sqrt(pow(astroidPosition.x - laserPosition.x, 2) + pow(astroidPosition.y - laserPosition.y, 2));
        const float hitBox = astroidSize / 2 + 1 / 2;

        if (distance <= hitBox) {
            return true;
        }
    }
    return false;
}

bool CollitionDetection::collitionDestroy(std::shared_ptr<Astroid>& astroid, Enemy& enemy) {
    const Vector3 enemyPosition = enemy.getPosition();
    const Vector3 astroidPosition = astroid -> getPosition();
    const float astroidSize = astroid -> getObjectSize();

    const float distance = sqrt(pow(astroidPosition.x - enemyPosition.x, 2) + pow(astroidPosition.y - enemyPosition.y, 2));
    const float hitBox = astroidSize / 2 + 5 / 2;

    if (distance <= hitBox){
        return true;
    }
    return false;
}

bool CollitionDetection::collitionDestroy(std::vector<Laser>& lasers, Enemy& enemy) {
    for (auto &laser : lasers) {
        const Vector3 shipPosition = enemy.getPosition();
        const Vector3 laserPosition = laser.getPosition();

        const float distance = sqrt(pow(shipPosition.x - laserPosition.x, 2) + pow(shipPosition.y - laserPosition.y, 2));
        const float hitBox = 5 / 2 + 1 / 2;

        if (distance <= hitBox){
            return true;
        }
    }
    return false;
}

bool CollitionDetection::collitionReset(std::shared_ptr<Astroid>& astroid, Ship& ship) {
    //CollitionReset functions check if a ship has collided and returns weather to reset the game.
    const Vector3 shipPosition = ship.getPosition();
    const Vector3 astroidPosition = astroid -> getPosition();
    const float astroidSize = astroid -> getObjectSize();


    const float distance = sqrt(pow(astroidPosition.x - shipPosition.x, 2) + pow(astroidPosition.y - shipPosition.y, 2));
    const float hitBox = astroidSize / 2 + 5 / 2;

    if (distance <= hitBox) {
        return true;
    }
    return false;
}

bool CollitionDetection::collitionReset(std::vector<Laser>& lasers, Ship& ship) {
    for (auto &laser : lasers) {
        const Vector3 shipPosition = ship.getPosition();
        const Vector3 laserPosition = laser.getPosition();


        const float distance = sqrt(pow(shipPosition.x - laserPosition.x, 2) + pow(shipPosition.y - laserPosition.y, 2));
        const float hitBox = 5 / 2 + 1 / 2;

        if (distance <= hitBox) {
            return true;
        }
    }
    return false;
}