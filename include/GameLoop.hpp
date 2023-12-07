#ifndef ASTROIDS_GAMELOOP_HPP
#define ASTROIDS_GAMELOOP_HPP

#include "CollitionDetection.hpp"
#include "Enemy.hpp"

class GameLoop{
public:

    GameLoop(const int boardSize, Ship& ship, std::shared_ptr<Scene>& scene);

    void reset();

    void createAstroids(const int astroidNumber);

    void createEnemies(const int ShipNumber);

    bool astroidUpdater(const float dt);

    bool enemyUpdater(const float dt);

    void explotionParticleUpdater(const float dt);

    int getScore() const;

    std::vector<std::shared_ptr<Astroid>> getAstroids();

    std::vector<Enemy> getEnemies();;

    void setShip(Ship& ship);

private:
    int boardSize_ = 0;
    int score_ = 0;
    std::vector<std::shared_ptr<Astroid>> astroids_;
    std::vector<ExplotionCreator> explotionParticles_;
    std::vector<Enemy> enemies_;
    Ship ship_;
    std::shared_ptr<Scene> scene_;
};

#endif//ASTROIDS_GAMELOOP_HPP