#ifndef PLACEHOLDER_ENEMY_HPP
#define PLACEHOLDER_ENEMY_HPP

#include "ObjectCreator.hpp"
#include "LaserControls.hpp"
#include <random>
#include <algorithm>

class Enemy {
public:
    Enemy(std::shared_ptr<Scene>& scene, int& boardSize) : scene_(scene), boardSize_(boardSize) {
    }
    void createEnemy(){
        for (int i = 0; i < 3; i++) {
            auto enemyShip_ = Object3D.createSprite("../textures/Tie Fighter.png", 5, 5);

            scene_->add(enemyShip_.first);
            enemyShips_.push_back(enemyShip_);
            shotTimer_.push_back(0);

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> distribution(-1, 1);
            std::bernoulli_distribution chooseAxis;
            std::bernoulli_distribution chooseSign;

            for (int j = 0; j < 4; j++) {
                if (chooseAxis(gen)) {
                    enemyShip_.first->position.x = chooseSign(gen) ? boardSize_ + 2 : -boardSize_ - 2;
                    enemyShip_.first->position.y = distribution(gen) * boardSize_ + 2;
                } else {
                    enemyShip_.first->position.y = chooseSign(gen) ? boardSize_ + 2 : -boardSize_ - 2;
                    enemyShip_.first->position.x = distribution(gen) * boardSize_ + 2;
                }
            }
        }
    }

    void moveEnemy(const std::vector<std::shared_ptr<Object>>& lasers, const std::shared_ptr<Sprite>& ship,
                   const std::vector<std::shared_ptr<Sprite>>& astroids, const std::vector<std::pair<float, float>>& astroidSpeeds,
                   const std::vector<std::pair<float, float>>& laserSpeeds){
        double turnScore = 0.5;
        if (shotTimer_.size() > enemyShips_.size()){
            int difference = shotTimer_.size() - enemyShips_.size();
            for (int i = 0; i < difference; i++){
                shotTimer_.erase(shotTimer_.begin());
            }
        }
        int i = 0;
        for (auto & enemyShip : enemyShips_){
            Vector2 directionEnemyShip(enemyShip.first->position.x, enemyShip.first->position.y);
            directionEnemyShip = directionEnemyShip.normalize();
            Vector2 direction(cos(enemyShip.first->rotation.z()), sin(enemyShip.first->rotation.z()));
            Vector2 directionShipEnemyShip(enemyShip.first->position.x - ship->position.x,
                                           enemyShip.first->position.y - ship->position.y);
            directionShipEnemyShip.normalize();
            for (int j = 0; j < astroids.size(); j++){
                Vector2 directionAstroid(astroidSpeeds[j].first, astroidSpeeds[j].second);
                directionAstroid = directionAstroid.normalize();
                double astroidShipDistance = sqrt(pow(enemyShip.first->position.x - astroids[j]->position.x, 2) +
                                                 pow(enemyShip.first->position.y - astroids[j]->position.y, 2)) / 2;
                if (direction[0] + 0.4 > -directionAstroid[0] &&
                    direction[1] + 0.4 > -directionAstroid[1]){
                    turnScore += 0.8 / astroidShipDistance/4;
                } else if (direction[0] - 0.4 < -directionAstroid[0] &&
                           direction[1] - 0.4 < -directionAstroid[1]){
                    turnScore -= 0.8 / astroidShipDistance/4;
                }
                if (directionEnemyShip[0] + 0.3 > -directionAstroid[0] &&
                    directionEnemyShip[1] + 0.3 > -directionAstroid[1]){
                    turnScore += 0.8 / astroidShipDistance/4;
                } else if (directionEnemyShip[0] - 0.3 < -directionAstroid[0] &&
                           directionEnemyShip[1] - 0.3 < -directionAstroid[1]){
                    turnScore -= 0.8 / astroidShipDistance/4;
                }
            }
            for (int j = 0; j < lasers.size(); j++){
                Vector2 directionLaser(laserSpeeds[j].first, laserSpeeds[j].second);
                directionLaser = directionLaser.normalize();
                if (direction[0] + 0.1 > directionLaser[0] &&
                    direction[1] + 0.1 > directionLaser[1]){
                    turnScore += 0.3;
                } else if (direction[0] - 0.1 < directionLaser[0] &&
                           direction[1] - 0.1 < directionLaser[1]){
                    turnScore -= 0.3;
                }
            }
            if (turnScore >= 0.55){
                enemyShip.first->rotation.z += M_PI/180 * dt_ * 50;
                enemyShip.second->rotation += M_PI/180 * dt_ * 50;
            } else if (turnScore <= 0.45){
                enemyShip.first->rotation.z -= M_PI/180 * dt_ * 50;
                enemyShip.second->rotation -= M_PI/180 * dt_ * 50;
            } else{
                float angle = atan2(ship->position.y - enemyShip.first->position.y, ship->position.x - enemyShip.first->position.x);
                if (enemyShip.first->rotation.z.operator/(1) < angle) {
                    enemyShip.first->rotation.z += M_PI/180 * dt_ * 50;
                    enemyShip.second->rotation += M_PI/180 * dt_ * 50;
                } else if (enemyShip.first->rotation.z.operator/(1) > angle) {
                    enemyShip.first->rotation.z -= M_PI/180 * dt_ * 50;
                    enemyShip.second->rotation -= M_PI/180 * dt_ * 50;
                }
                if (shotTimer_[i] >= 0.4) {
                    laserControls_.createLasar(scene_, enemyShip.first);
                    shotTimer_[i] = 0;
                }
            }
            direction[0] = (cos(enemyShip.first->rotation.z()));
            direction[1] = (sin(enemyShip.first->rotation.z()));
            enemyShip.first->position.x += 15 * dt_ * direction[0];
            enemyShip.first->position.y += 15 * dt_ * direction[1];
            laserControls_.setLasarSpeed(direction[0], direction[1]);
            shotTimer_[i] += dt_;
            turnScore = 0.5;
            if (enemyShip.first->position.x >= boardSize_ + 2 || enemyShip.first->position.x <= -boardSize_ - 2){
                enemyShip.first->position.x *= -0.9;
            }
            if (enemyShip.first->position.y >= boardSize_ + 2 || enemyShip.first->position.y <= -boardSize_ - 2){
                enemyShip.first->position.y *= -0.9;
            }
            i += 1;
        }
        i = 0;
        laserControls_.updateLasars(scene_, dt_, boardSize_);
    }

    void setDt (float dt){
        dt_ = dt;
    }

    std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& getEnemyShips(){
        return enemyShips_;
    }

    std::vector<std::shared_ptr<Object>>& getLasars(){
        return laserControls_.getLasers();
    }

private:
    std::shared_ptr<Scene> scene_;
    Object Object3D;
    LaserControls laserControls_;
    std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>> enemyShips_;
    std::vector<float> shotTimer_;
    float dt_ = 0;
    int boardSize_ = 0;
};

#endif //PLACEHOLDER_ENEMY_HPP