#ifndef PLACEHOLDER_ASTROID_HPP
#define PLACEHOLDER_ASTROID_HPP

#include "ObjectCreator.hpp"
#include <random>
#include <algorithm>

class Astroid{
public:
    Astroid(int& boardSize) : boardSize_(boardSize) {
    }
    void createAstroids(const std::shared_ptr<Scene>& scene){
        for (int i = 0; i < 2; i++) {
            auto astroid = Object3D.createSprite("../textures/Astroid.png", 5, 5).first;
            astroids_.push_back(astroid);

            scene->add(astroid);

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> distribution(-1, 1);
            std::bernoulli_distribution chooseAxis;
            std::bernoulli_distribution chooseSign;

            for (int j = 0; j < 4; j++) {
                if (chooseAxis(gen)) {
                    astroid->position.x = chooseSign(gen) ? boardSize_ + 2 : -boardSize_ - 2;
                    astroid->position.y = distribution(gen) * boardSize_ + 2;
                } else {
                    astroid->position.y = chooseSign(gen) ? boardSize_ + 2 : -boardSize_ - 2;
                    astroid->position.x = distribution(gen) * boardSize_ + 2;
                }
            }

            std::uniform_int_distribution<int> speedDistribution(minSpeed_, maxSpeed_);     // Kode fra ChatGPT
            astroidSpeeds_.emplace_back(speedDistribution(gen), speedDistribution(gen));   //Slutt kode fra ChatGPT
        }
    }

    void updateAstroids(const std::shared_ptr<Scene>& scene, const float dt) {
        for (long long i = 0; i < astroids_.size(); i++) {
            auto astroid = astroids_[i];
            astroid->position.x += astroidSpeeds_[i].first * dt;
            astroid->position.y += astroidSpeeds_[i].second * dt;

            if (astroid->position.x > boardSize_ + 2 || astroid->position.x < -boardSize_ - 2 || astroid->position.y > boardSize_ + 2 || astroid->position.y < -boardSize_ - 2) {
                scene->remove(*astroid);
                astroids_.erase(astroids_.begin() + i);
                astroidSpeeds_.erase(astroidSpeeds_.begin() + i);
                i--;
            }
        }
    }
    void checkColison(const std::vector<std::shared_ptr<Object>>& lasers, const std::shared_ptr<Sprite>& ship,
                      const std::shared_ptr<Scene>& scene, std::vector<std::pair<std::shared_ptr<Sprite>,
                              std::shared_ptr<SpriteMaterial>>>& enemyShips, const std::vector<std::shared_ptr<Object>>& enemyLasers){     //Denne funksjonen er for det meste min kode, litt ChatGPT til feilretting, og litt hjelp fra medstudent.
        for (auto as = astroids_.begin(); as != astroids_.end();) {
            auto &astroid = **as;
            for (int i = 0; i < astroids_.size(); i++){
                if (astroids_[i]->position.x + astroidHitBox_ > astroid.position.x &&
                    astroids_[i]->position.x < astroid.position.x + astroidHitBox_ &&
                    astroids_[i]->position.y + astroidHitBox_ > astroid.position.y &&
                    astroids_[i]->position.y < astroid.position.y + astroidHitBox_){
                    if (i == std::distance(astroids_.begin(), as)){
                        continue;
                    } else {
                        Vector2 collisonDirection(astroids_[i]->position.x - astroids_[std::distance(astroids_.begin(), as)]->position.x,
                                                  astroids_[i]->position.y - astroids_[std::distance(astroids_.begin(), as)]->position.y);
                        collisonDirection.normalize();
                        Vector2 speedI(astroidSpeeds_[i].first, astroidSpeeds_[i].second);
                        Vector2 speedAS(astroidSpeeds_[std::distance(astroids_.begin(), as)].first,
                                        astroidSpeeds_[std::distance(astroids_.begin(), as)].second);
                        astroidSpeeds_[i].first = speedAS.length() * collisonDirection[0];
                        astroidSpeeds_[i].second = speedAS.length() * collisonDirection[1];
                        astroidSpeeds_[std::distance(astroids_.begin(), as)].first = speedI.length() * -collisonDirection[0];
                        astroidSpeeds_[std::distance(astroids_.begin(), as)].second = speedI.length() * -collisonDirection[1];
                    }
                }
            }
            auto es = enemyShips.begin();
            while (es != enemyShips.end()){
                auto enemyShip = *es;
                if (enemyShip.first->position.x + astroidHitBox_ > astroid.position.x &&
                    enemyShip.first->position.x < astroid.position.x + astroidHitBox_ &&
                    enemyShip.first->position.y + astroidHitBox_ > astroid.position.y &&
                    enemyShip.first->position.y < astroid.position.y + astroidHitBox_){
                    scene->remove(*enemyShip.first);
                    es = enemyShips.erase(es);
                } else{
                    es++;
                }
            }
            auto ls = lasers.begin();
            while (ls != lasers.end()) {
                auto laser = *ls;
                if (laser->position.x + astroidHitBox_ > astroid.position.x &&
                    laser->position.x < astroid.position.x + astroidHitBox_ &&
                    laser->position.y + astroidHitBox_ > astroid.position.y &&
                    laser->position.y < astroid.position.y + astroidHitBox_) {
                    scene->remove(astroid);
                    as = astroids_.erase(as);
                    astroidSpeeds_.erase(astroidSpeeds_.begin() + std::distance(astroids_.begin(), as));
                    score_++;
                } else {
                    ls++;
                }
                es = enemyShips.begin();
                while (es != enemyShips.end()) {
                    auto enemyShip = *es;
                    if (enemyShip.first->position.x + astroidHitBox_ > laser->position.x &&
                        enemyShip.first->position.x < laser->position.x + astroidHitBox_ &&
                        enemyShip.first->position.y + astroidHitBox_ > laser->position.y &&
                        enemyShip.first->position.y < laser->position.y + astroidHitBox_) {
                        scene->remove(*enemyShip.first);
                        es = enemyShips.erase(es);
                        score_ += 5;
                    }
                    else{
                        es++;
                    }
                }
            }
            auto els = enemyLasers.begin();
            while (els != enemyLasers.end()) {
                auto laser = *els;
                if (ship->position.x + astroidHitBox_ > laser->position.x &&
                    ship->position.x < laser->position.x + astroidHitBox_ &&
                    ship->position.y + astroidHitBox_ > laser->position.y &&
                    ship->position.y < laser->position.y + astroidHitBox_) {
                    ship->position.x = 0;
                    ship->position.y = 0;
                    score_ = 0;
                }
                if (laser->position.x + astroidHitBox_ > astroid.position.x &&
                    laser->position.x < astroid.position.x + astroidHitBox_ &&
                    laser->position.y + astroidHitBox_ > astroid.position.y &&
                    laser->position.y < astroid.position.y + astroidHitBox_) {
                    scene->remove(astroid);
                    as = astroids_.erase(as);
                    astroidSpeeds_.erase(astroidSpeeds_.begin() + std::distance(astroids_.begin(), as));
                } else {
                    els++;
                }
            }
            if (ls == lasers.end() && as != astroids_.end()) {
                as++;
            }
            if (ship->position.x + astroidHitBox_ > astroid.position.x &&
                ship->position.x < astroid.position.x + astroidHitBox_ &&
                ship->position.y + astroidHitBox_ > astroid.position.y &&
                ship->position.y < astroid.position.y + astroidHitBox_) {
                ship->position.x = 0;
                ship->position.y = 0;
                score_ = 0;
            }
        }
    }

    [[nodiscard]] int& getScore() {
        return score_;
    }

    std::vector<std::shared_ptr<Sprite>>& getAstroids(){
        return astroids_;
    }

    std::vector<std::pair<float, float>>& getAstroidSpeeds(){
        return astroidSpeeds_;
    }

private:
    std::vector<std::shared_ptr<Sprite>> astroids_;
    std::vector<std::pair<float, float>> astroidSpeeds_;
    Object Object3D;
    Scene scene_;
    int boardSize_;
    const float astroidHitBox_ = 3.5;
    const int minSpeed_ = -20;
    const int maxSpeed_ = 20;
    int score_ = 0;
};

#endif //PLACEHOLDER_ASTROID_HPP