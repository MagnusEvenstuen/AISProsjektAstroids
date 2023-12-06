#define _USE_MATH_DEFINES

#include "Enemy.hpp"
#include <random>

Enemy::Enemy(std::shared_ptr<Scene>& scene, const int& boardSize): scene_(scene){
    //Creation of the enemy. Random start position.

    std::filesystem::path texturePath = __FILE__;
    texturePath = texturePath.parent_path().parent_path();
    texturePath += "/textures/Tie Fighter.png";

    sprite_ = ObjectCreator::createSprite(5, 5, texturePath.string());
    boardSize_ = boardSize;

    scene_ -> add(sprite_.first);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution <float> yPosStart(-boardSize_, boardSize_);

    sprite_.first -> position.x = -boardSize_;
    sprite_.first -> position.y = yPosStart(gen);

    speedMultiplier_ = 15;
}

void Enemy::moveEnemy(const std::shared_ptr<Sprite> & ship,
                      std::vector<std::shared_ptr<Astroid>>& astroids,
                      const float dt) {
    //Maths to move the enemy based on the position of other objects.
    shotTimer_ += dt;

    double turnScore = 0.5;
    Vector2 directionEnemyShip(sprite_.first -> position.x, sprite_.first -> position.y);
    directionEnemyShip = directionEnemyShip.normalize();
    Vector2 direction(cos(sprite_.first -> rotation.z()), sin(sprite_.first -> rotation.z()));
    Vector2 directionShipEnemyShip(sprite_.first -> position.x - ship -> position.x,
                                   sprite_.first -> position.y - ship -> position.y);
    directionShipEnemyShip.normalize();
    for (const auto & astroid : astroids) {
        Vector2 directionAstroid(astroid -> getObjectSpeed().x, astroid -> getObjectSpeed().y);
        directionAstroid = directionAstroid.normalize();
        double astroidShipDistance = sqrt(pow(sprite_.first -> position.x - astroid -> getPosition().x, 2) +
                                          pow(sprite_.first -> position.y - astroid -> getPosition().y, 2)) / 2;
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
        sprite_.first -> rotation.z += M_PI / 180 * dt * 50;
        sprite_.second -> rotation += M_PI / 180 * dt * 50;
    } else if (turnScore <= 0.45) {
        sprite_.first -> rotation.z -= M_PI / 180 * dt * 50;
        sprite_.second -> rotation -= M_PI / 180 * dt * 50;
    } else {
        float angle = atan2(ship -> position.y - sprite_.first -> position.y, ship -> position.x - sprite_.first -> position.x);
        if (sprite_.first -> rotation.z.operator / (1) < angle) {
            sprite_.first -> rotation.z += M_PI / 180 * dt * 50;
            sprite_.second -> rotation += M_PI / 180 * dt * 50;
        } else if (sprite_.first -> rotation.z.operator / (1) > angle) {
            sprite_.first -> rotation.z -= M_PI / 180 * dt * 50;
            sprite_.second -> rotation -= M_PI / 180 * dt * 50;
        }
        if (shotTimer_ >= 0.4) {
            lasers_.emplace_back(objectSpeed_, sprite_.first->position, scene_);
            shotTimer_ = 0;
        }
    }

    objectSpeed_[0] = (cos(sprite_.first -> rotation.z()));
    objectSpeed_[1] = (sin(sprite_.first -> rotation.z()));

    BaseShip::moveShip(dt, boardSize_);

    BaseShip::updateLasers(dt, scene_);
}

std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>& Enemy::getEnemyShips() {
    return sprite_;
}