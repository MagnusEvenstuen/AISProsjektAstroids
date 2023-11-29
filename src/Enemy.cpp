#define _USE_MATH_DEFINES

#include "Enemy.hpp"
#include <cmath>

void Enemy::createEnemy() {
    for (int i = 0; i < 2; i++) {
        auto enemyShip_ = Object3D.createSprite(5, 5, "../textures/Tie Fighter.png");

        scene_ -> add(enemyShip_.first);
        enemyShips_.push_back(enemyShip_);
        shotTimer_.push_back(0);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution < float > yPosStart(-boardSize_, boardSize_);

        enemyShip_.first -> position.x = -boardSize_;
        enemyShip_.first -> position.y = yPosStart(gen);
    }
}

void Enemy::moveEnemy(const std::shared_ptr<Sprite> & ship,
                      const std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& astroids,
                      const std::vector<Vector2>& astroidSpeeds) {
    double turnScore = 0.5;
    if (shotTimer_.size() > enemyShips_.size()) {
        int difference = shotTimer_.size() - enemyShips_.size();
        for (int i = 0; i < difference; i++) {
            shotTimer_.erase(shotTimer_.begin());
        }
    }
    int i = 0;
    for (auto & enemyShip: enemyShips_) {
        Vector2 directionEnemyShip(enemyShip.first -> position.x, enemyShip.first -> position.y);
        directionEnemyShip = directionEnemyShip.normalize();
        Vector2 direction(cos(enemyShip.first -> rotation.z()), sin(enemyShip.first -> rotation.z()));
        Vector2 directionShipEnemyShip(enemyShip.first -> position.x - ship -> position.x,
                                       enemyShip.first -> position.y - ship -> position.y);
        directionShipEnemyShip.normalize();
        for (int j = 0; j < astroids.size(); j++) {
            Vector2 directionAstroid(astroidSpeeds[j].x, astroidSpeeds[j].y);
            directionAstroid = directionAstroid.normalize();
            double astroidShipDistance = sqrt(pow(enemyShip.first -> position.x - astroids[j].first -> position.x, 2) +
                                              pow(enemyShip.first -> position.y - astroids[j].first -> position.y, 2)) / 2;
            if (direction[0] + 0.4 > -directionAstroid[0] &&
                direction[1] + 0.4 > -directionAstroid[1]) {
                turnScore += 0.8 / astroidShipDistance / 4;
            } else if (direction[0] - 0.4 < -directionAstroid[0] &&
                       direction[1] - 0.4 < -directionAstroid[1]) {
                turnScore -= 0.8 / astroidShipDistance / 4;
            }
            if (directionEnemyShip[0] + 0.3 > -directionAstroid[0] &&
                directionEnemyShip[1] + 0.3 > -directionAstroid[1]) {
                turnScore += 0.8 / astroidShipDistance / 4;
            } else if (directionEnemyShip[0] - 0.3 < -directionAstroid[0] &&
                       directionEnemyShip[1] - 0.3 < -directionAstroid[1]) {
                turnScore -= 0.8 / astroidShipDistance / 4;
            }
        }
        if (turnScore >= 0.55) {
            enemyShip.first -> rotation.z += M_PI / 180 * dt_ * 50;
            enemyShip.second -> rotation += M_PI / 180 * dt_ * 50;
        } else if (turnScore <= 0.45) {
            enemyShip.first -> rotation.z -= M_PI / 180 * dt_ * 50;
            enemyShip.second -> rotation -= M_PI / 180 * dt_ * 50;
        } else {
            float angle = atan2(ship -> position.y - enemyShip.first -> position.y, ship -> position.x - enemyShip.first -> position.x);
            if (enemyShip.first -> rotation.z.operator / (1) < angle) {
                enemyShip.first -> rotation.z += M_PI / 180 * dt_ * 50;
                enemyShip.second -> rotation += M_PI / 180 * dt_ * 50;
            } else if (enemyShip.first -> rotation.z.operator / (1) > angle) {
                enemyShip.first -> rotation.z -= M_PI / 180 * dt_ * 50;
                enemyShip.second -> rotation -= M_PI / 180 * dt_ * 50;
            }
            if (shotTimer_[i] >= 0.4) {
                laserControls_.setLaserSpeed(direction[0], direction[1]);
                laserControls_.createLaser(scene_, enemyShip.first);
                shotTimer_[i] = 0;
            }
        }
        direction[0] = (cos(enemyShip.first -> rotation.z()));
        direction[1] = (sin(enemyShip.first -> rotation.z()));

        ObjectUpdater::moveObject(enemyShips_[i].first, direction, dt_, 15);
        ObjectUpdater::loopObject(enemyShips_[i].first, boardSize_);

        shotTimer_[i] += dt_;
        turnScore = 0.5;
        i += 1;
    }
    laserControls_.updateLasers(scene_, dt_, boardSize_);
}

void Enemy::setDt(float dt) {
    dt_ = dt;
}

std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>> & Enemy::getEnemyShips() {
    return enemyShips_;
}

std::vector< std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& Enemy::getLasers() {
    return laserControls_.getLasers();
}