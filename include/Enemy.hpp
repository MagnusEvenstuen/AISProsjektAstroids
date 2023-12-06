#ifndef ASTROIDS_ENEMY_HPP
#define ASTROIDS_ENEMY_HPP

#include "Astroid.hpp"
#include "BaseShip.hpp"
#include "ObjectCreator.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

class Enemy : public BaseShip{
public:
    Enemy(std::shared_ptr<Scene>& scene, const int& boardSize);

    void moveEnemy(const std::shared_ptr<Sprite>& ship, std::vector<std::shared_ptr<Astroid>>& astroids,
                   const float dt);

    std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>& getEnemyShips();

private:
    std::shared_ptr<Scene> scene_;
    float shotTimer_ = 0;
};

#endif //ASTROIDS_ENEMY_HPP