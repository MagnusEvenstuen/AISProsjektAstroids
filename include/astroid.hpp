#ifndef PLACEHOLDER_ASTROID_HPP
#define PLACEHOLDER_ASTROID_HPP

#include "ObjectCreator.hpp"
#include <random>
#include <algorithm>
#include <iostream>

class Astroid{
public:
    void createAstroids(const std::shared_ptr<Scene>& scene, const float& startPos){
        for (int i = 0; i < 2; i++) {
            material_->map = texture_;
            material_->map->offset.set(0.5, 0.5);
            auto astroid = Sprite::create(material_);
            astroid->scale.set(5, 5, 0);
            astroids_.push_back(astroid);
            creationTime_.push_back(0);


            scene->add(astroid);

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> distribution(-1, 1);
            std::bernoulli_distribution chooseAxis;
            std::bernoulli_distribution chooseSign;

            for (int j = 0; j < 4; j++) {
                if (chooseAxis(gen)) {
                    astroid->position.x = chooseSign(gen) ? startPos : -startPos;
                    astroid->position.y = distribution(gen) * startPos;
                } else {
                    astroid->position.y = chooseSign(gen) ? startPos : -startPos;
                    astroid->position.x = distribution(gen) * startPos;
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
            creationTime_[i] += dt;

            if (astroid->position.x > 32 || astroid->position.x < -32 || astroid->position.y > 32 || astroid->position.y < -32) {
                scene->remove(*astroid);
                astroids_.erase(astroids_.begin() + i);
                creationTime_.erase(creationTime_.begin() + i);
                astroidSpeeds_.erase(astroidSpeeds_.begin() + i);
                i--;
            }
        }
    }
    void checkColison(const std::vector<std::shared_ptr<Object>>& lasars, std::shared_ptr<Mesh> &ship, const std::shared_ptr<Scene>& scene){     //Denne funksjonen er for det meste min kode, litt ChatGPT til feilretting, og litt hjelp fra medstudent.
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
            auto ls = lasars.begin();
            while (ls != lasars.end()) {
                auto lasar = *ls;
                if (lasar->position.x + astroidHitBox_ > astroid.position.x &&
                    lasar->position.x < astroid.position.x + astroidHitBox_ &&
                    lasar->position.y + astroidHitBox_ > astroid.position.y &&
                    lasar->position.y < astroid.position.y + astroidHitBox_) {
                    scene->remove(astroid);
                    as = astroids_.erase(as);
                    astroidSpeeds_.erase(astroidSpeeds_.begin() + std::distance(astroids_.begin(), as));
                    score_++;
                } else {
                    ls++;
                }
            }
            if (ls == lasars.end() && as != astroids_.end()) {
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

    [[nodiscard]] int getScore() const{
        return score_;
    }

private:
    std::vector<std::shared_ptr<Sprite>> astroids_;
    std::vector<float> creationTime_;
    std::vector<std::pair<float, float>> astroidSpeeds_;
    const std::shared_ptr<Texture> texture_ = TextureLoader().load("../textures/Astroid.png");
    std::shared_ptr<SpriteMaterial> material_ = SpriteMaterial::create();
    const float astroidHitBox_ = 3.5;
    const int minSpeed_ = -20;
    const int maxSpeed_ = 20;
    int score_ = 0;
};

#endif //PLACEHOLDER_ASTROID_HPP