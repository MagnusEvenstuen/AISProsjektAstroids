#ifndef PLACEHOLDER_ASTROID_HPP
#define PLACEHOLDER_ASTROID_HPP

#include <objectCreator.hpp>
#include <random>
#include <iostream>
#include <algorithm>

class Astroid{
public:
    void createAstroids(const std::shared_ptr<Scene>& scene){
        for (int i = 0; i < 2; i++) {
            auto astroid = std::make_shared<Object>();
            astroids_.push_back(astroid);
            creationTime_.push_back(0);
            astroid->setColor(Color::white);
            scene->add(*astroid);

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> distribution(-1, 1);
            std::bernoulli_distribution chooseAxis;
            std::bernoulli_distribution chooseSign;

            for (int j = 0; j < 4; j++) {
                if (chooseAxis(gen)) {
                    astroid->position.x = chooseSign(gen) ? 30 : -30;
                    astroid->position.y = distribution(gen) * 30;
                } else {
                    astroid->position.y = chooseSign(gen) ? 30 : -30;
                    astroid->position.x = distribution(gen) * 30;
                }
            }

            std::uniform_int_distribution<int> speedDistribution(minSpeed_, maxSpeed_);     // Kode fra ChatGPT
            astroidSpeeds_.emplace_back(speedDistribution(gen), speedDistribution(gen));   //Slutt kode fra ChatGPT
        }
    }

    void updateAstroids(const std::shared_ptr<Scene>& scene, const float dt) {
        for (size_t i = 0; i < astroids_.size(); i++) {
            auto astroid = astroids_[i];
            astroid->position.x += astroidSpeeds_[i].first * dt;
            astroid->position.y += astroidSpeeds_[i].second * dt;
            creationTime_[i] += dt;

            if (astroid->position.x > 30 || astroid->position.x < -30 || astroid->position.y > 30 || astroid->position.y < -30) {
                scene->remove(*astroid);
                astroids_.erase(astroids_.begin() + i);
                creationTime_.erase(creationTime_.begin() + i);
                astroidSpeeds_.erase(astroidSpeeds_.begin() + i);
                i--;
            }

        }
    }
    void checkColison(const std::vector<std::shared_ptr<Object>>& lasars, std::shared_ptr<Object>& ship, const std::shared_ptr<Scene>& scene){     //Denne funksjonen er for det meste min kode, litt ChatGPT til feilretting, og litt hjelp fra medstudent.
        for (auto as = astroids_.begin(); as != astroids_.end();) {
            auto &astroid = **as;
            auto ls = lasars.begin();
            while (ls != lasars.end()) {
                auto lasar = *ls;
                if (lasar->position.x + 1 > astroid.position.x &&
                    lasar->position.x < astroid.position.x + 1 &&
                    lasar->position.y + 1 > astroid.position.y &&
                    lasar->position.y < astroid.position.y + 1) {
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
        }
        for (auto as = astroids_.begin(); as < astroids_.end(); as++) {
            auto &astroid = **as;
            if (ship->position.x + 1 > astroid.position.x &&
                ship->position.x < astroid.position.x + 1 &&
                ship->position.y + 1 > astroid.position.y &&
                ship->position.y < astroid.position.y + 1) {
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
    std::vector<std::shared_ptr<Object>> astroids_;
    std::vector<float> creationTime_;
    std::vector<std::pair<float, float>> astroidSpeeds_;
    int minSpeed_ = -20;
    int maxSpeed_ = 20;
    int score_ = 0;
};

#endif //PLACEHOLDER_ASTROID_HPP