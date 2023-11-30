#ifndef ASTROIDS_ENEMY_HPP
#define ASTROIDS_ENEMY_HPP

#include "threepp/threepp.hpp"
#include "ObjectCreator.hpp"
#include "LaserControls.hpp"

using namespace threepp;

class Enemy {
public:
    Enemy(std::shared_ptr<Scene>& scene, const int& boardSize) : scene_(scene), boardSize_(boardSize) {
    }
    void createEnemy();

    void moveEnemy(const std::shared_ptr<Sprite>& ship, const std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& astroids,
                   const std::vector<Vector2>& astroidSpeeds);

    void setDt (float dt);

    std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& getEnemyShips();

    std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& getLasers();

private:
    std::shared_ptr<Scene> scene_;
    ObjectCreator Object3D;
    LaserControls laserControls_;
    std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>> enemyShips_;
    std::vector<float> shotTimer_;
    float dt_ = 0;
    int boardSize_ = 0;
};

#endif //ASTROIDS_ENEMY_HPP