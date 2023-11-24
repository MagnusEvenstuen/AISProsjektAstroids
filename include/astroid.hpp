#ifndef ASTROIDS_ASTROID_HPP
#define ASTROIDS_ASTROID_HPP

#include "ObjectCreator.hpp"
#include <random>


class Astroid{
public:
    Astroid(const int& boardSize) : boardSize_(boardSize) {
    }
    void createAstroids(const std::shared_ptr<Scene>& scene){
        for (int i = 0; i < 2; i++) {
            auto astroid = Object3D.createSprite(5, 5, "../textures/Astroid.png");
            astroids_.push_back(astroid);

            scene->add(astroid.first);

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> distribution(-1, 1);
            std::bernoulli_distribution chooseAxis;
            std::bernoulli_distribution chooseSign;

            for (int j = 0; j < 4; j++) {
                if (chooseAxis(gen)) {
                    astroid.first->position.x = chooseSign(gen) ? boardSize_ + 2 : -boardSize_ - 2;
                    astroid.first->position.y = distribution(gen) * boardSize_ + 2;
                } else {
                    astroid.first->position.y = chooseSign(gen) ? boardSize_ + 2 : -boardSize_ - 2;
                    astroid.first->position.x = distribution(gen) * boardSize_ + 2;
                }
            }

            std::uniform_int_distribution<int> speedDistribution(minSpeed_, maxSpeed_);     // Kode fra ChatGPT
            astroidSpeeds_.emplace_back(speedDistribution(gen), speedDistribution(gen));   //Slutt kode fra ChatGPT
        }
    }

    void updateAstroids(const std::shared_ptr<Scene>& scene, const float dt) {
        for (long long i = 0; i < astroids_.size(); i++) {
            auto astroid = astroids_[i];
            astroid.first->position.x += astroidSpeeds_[i].first * dt;
            astroid.first->position.y += astroidSpeeds_[i].second * dt;

            if (astroid.first->position.x > boardSize_ + 2 || astroid.first->position.x < -boardSize_ - 2 || astroid.first->position.y > boardSize_ + 2 || astroid.first->position.y < -boardSize_ - 2) {
                scene->remove(*astroid.first);
                astroids_.erase(astroids_.begin() + i);
                astroidSpeeds_.erase(astroidSpeeds_.begin() + i);
                i--;
            }
        }
    }


    std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& getAstroids(){
        return astroids_;
    }

    std::vector<std::pair<float, float>>& getAstroidSpeeds(){
        return astroidSpeeds_;
    }

private:
    std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>> astroids_;
    std::vector<std::pair<float, float>> astroidSpeeds_;
    Object Object3D;
    Scene scene_;
    int boardSize_;
    const int minSpeed_ = -20;
    const int maxSpeed_ = 20;
};

#endif //ASTROIDS_ASTROID_HPP