#ifndef PLACEHOLDER_ASTROID_HPP
#define PLACEHOLDER_ASTROID_HPP

#include <objectCreator.hpp>
#include <random>
#include <iostream>

using namespace threepp;
namespace {
    class Astroid{
    public:
        void createAstroids(const std::shared_ptr<Scene> scene){
            for (int i = 0; i < 2; i++) {
                auto astroid = std::make_shared<Object>();
                astroids_.push_back(astroid);
                creationTime_.push_back(0);
                astroid->setColor(Color::white);
                scene->add(*astroid);

                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<int> distribution(-25, 25);
                if (i % 2 == 0) {
                    astroid->position.y = distribution(gen);
                    astroid->position.x = 29;
                } else {
                    astroid->position.y = 29;
                    astroid->position.x = -distribution(gen);
                }

                std::uniform_int_distribution<int> speedDistribution(minSpeed_, maxSpeed_);     // Kode fra ChatGPT
                astroidSpeeds_.push_back(std::make_pair(speedDistribution(gen), speedDistribution(gen)));   //Slutt kode fra ChatGPT
            }
        }

        void updateAstroids(const std::shared_ptr<Scene> scene, const double dt) {
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

    private:
        std::vector<std::shared_ptr<Object>> astroids_;
        std::vector<double> creationTime_;
        std::vector<std::pair<int, int>> astroidSpeeds_;
        int minSpeed_ = -20;
        int maxSpeed_ = 20;
    };
}

#endif //PLACEHOLDER_ASTROID_HPP