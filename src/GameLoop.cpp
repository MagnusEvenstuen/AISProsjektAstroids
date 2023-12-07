#include "GameLoop.hpp"
#include <iostream>

GameLoop::GameLoop(const int boardSize, Ship& ship, std::shared_ptr<Scene>& scene)
        : boardSize_(boardSize), ship_(ship), scene_(scene){
}

void GameLoop::reset() {
    for (auto &astroid :astroids_){     //Tømmer scena og sletter alle objekt
        scene_ -> remove(*astroid->getSprite());
    }
    for (auto &enemy : enemies_){
        scene_ -> remove(*enemy.getSprite());
        std::vector<Laser> lasers = enemy.getLaser();
        for (auto &laser : lasers){
            scene_ -> remove(*laser.getSprite());
        }
    }
    astroids_.clear();
    enemies_.clear();
    score_ = 0;
}

void GameLoop::createAstroids(const int astroidNumber) {
    for (int i = 0; i < astroidNumber; i++){
        astroids_.emplace_back(std::make_shared<Astroid>(boardSize_, scene_));
        //std::cout << astroids_.size() <<std::endl;
    }
}

void GameLoop::createEnemies(const int ShipNumber) {
    for (int i = 0; i < ShipNumber; i++){
        enemies_.emplace_back(scene_, boardSize_);
    }
}

bool GameLoop::astroidUpdater(const float dt) {
    bool reset = false;     //Updates astroids and delets what should be deleted.
    for (auto it = astroids_.begin(); it != astroids_.end();){
        auto astroid = *it;
        astroid->checkAstroidCollition(astroids_);
        bool remove = astroid -> update(dt);
        bool destroyed = CollitionDetection::collitionDestroy(astroid, ship_.getLaser());

        if (!destroyed) {
            for (auto es = enemies_.begin(); es != enemies_.end();){
                auto enemy = *es;
                destroyed = CollitionDetection::collitionDestroy(astroid, enemy.getLaser());
                bool destroyEnemy = CollitionDetection::collitionDestroy(astroid, enemy);

                if (destroyEnemy){
                    scene_ ->remove(*enemy.getSprite());
                    std::vector<Laser> lasers = enemy.getLaser();

                    for (auto &laser : lasers){
                        scene_ -> remove(*laser.getSprite());
                    }
                    es = enemies_.erase(es);
                    for (int i = 0; i < 50; i++){
                        explotionParticles_.emplace_back(scene_, enemy.getPosition());
                    }
                } else {
                    es++;
                }

                if (destroyed){
                    score_ -= 1;
                    break;
                }
            }
        }

        if (remove){
            scene_ -> remove(*astroid->getSprite());
            it = astroids_.erase(it);
        } else if (destroyed) {
            for (int i = 0; i < 50; i++){
                explotionParticles_.emplace_back(scene_, astroid->getPosition());
            }
            score_++;
            scene_ -> remove(*astroid->getSprite());
            it = astroids_.erase(it);
        } else {
            it++;
        }

        if (!reset) {
            reset = CollitionDetection::collitionReset(astroid, ship_);
        }
    }
    return reset;
}

bool GameLoop::enemyUpdater(const float dt) {
    bool reset = false;     //Updates enemy and delets what should be deleted
    for (auto es = enemies_.begin(); es != enemies_.end();){
        auto& enemy = *es;
        enemy.moveEnemy(ship_.getSprite(), astroids_, dt);
        bool destroy = CollitionDetection::collitionDestroy(ship_.getLaser(), enemy);
        std::vector<Laser> lasesrs = ship_.getLaser();

        if (destroy) {
            std::vector<Laser> lasers = enemy.getLaser();
            score_++;

            for (auto &laser : lasers){
                scene_ -> remove(*laser.getSprite());
            }

            for (int i = 0; i < 50; i++){
                explotionParticles_.emplace_back(scene_, enemy.getPosition());
            }

            scene_ -> remove(*enemy.getSprite());
            es = enemies_.erase(es);
        } else {
            es++;
        }
        std::vector<Laser> enemyLasers = enemy.getLaser();
        reset = CollitionDetection::collitionReset(enemyLasers, ship_);
    }
    return reset;
}

void GameLoop::explotionParticleUpdater(const float dt) {
    //Updates explotion particles.
    for (auto it = explotionParticles_.begin(); it != explotionParticles_.end();){
        auto& explotionParticle = *it;
        bool remove = explotionParticle.update(dt);

        if (remove){
            scene_ -> remove(*explotionParticle.getSprite());
            it = explotionParticles_.erase(it);
        } else {
            it++;
        }
    }
}

int GameLoop::getScore() const {
    return score_;
}

std::vector<std::shared_ptr<Astroid>> GameLoop::getAstroids() {
    return astroids_;
}

std::vector<Enemy> GameLoop::getEnemies() {
    return enemies_;
}

void GameLoop::setShip(Ship& ship) {
    ship_ = ship;
}