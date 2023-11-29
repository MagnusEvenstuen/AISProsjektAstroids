#include "Astroid.hpp"
#include "ObjectUpdater.hpp"
#include <random>


void Astroid::createAstroids(const std::shared_ptr < Scene > & scene) {
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = 0; i < 2; i++) {
        std::uniform_real_distribution < float > size(3, 10);
        astroidSize_.push_back(size(gen));
        auto astroid = Object3D.createSprite(astroidSize_.back(), astroidSize_.back(), "../textures/Astroid.png");
        astroids_.push_back(astroid);

        std::uniform_real_distribution < float > rotation(0, 2 * 3.14159265);
        astroidRotation_.push_back(rotation(gen));

        scene -> add(astroid.first);

        std::uniform_real_distribution < float > distribution(-1, 1);
        std::bernoulli_distribution chooseSign;

        for (int j = 0; j < 4; j++) {
            if (chooseSign(gen)) {
                astroid.first -> position.x = chooseSign(gen) ? boardSize_ + 2 : -boardSize_ - 2;
                astroid.first -> position.y = distribution(gen) * boardSize_ + 2;
            } else {
                astroid.first -> position.y = chooseSign(gen) ? boardSize_ + 2 : -boardSize_ - 2;
                astroid.first -> position.x = distribution(gen) * boardSize_ + 2;
            }
        }

        std::uniform_int_distribution < int > speedDistribution(minSpeed_, maxSpeed_); // Kode fra ChatGPT
        astroidSpeeds_.emplace_back(speedDistribution(gen), speedDistribution(gen)); //Slutt kode fra ChatGPT
    }
}

void Astroid::updateAstroids(std::shared_ptr < Scene > & scene,
                             const float dt) {
    for (long long i = 0; i < astroids_.size(); i++) {
        ObjectUpdater::moveObject(astroids_[i], astroidSpeeds_[i], astroidRotation_[i], dt);

        bool destroyAstroid = ObjectUpdater::destroyObject(astroids_[i].first, boardSize_, scene);
        if (destroyAstroid) {
            astroids_.erase(astroids_.begin() + i);
            astroidSpeeds_.erase(astroidSpeeds_.begin() + i);
            astroidRotation_.erase(astroidRotation_.begin() + i);
            astroidSize_.erase(astroidSize_.begin() + i);
            i--;
        }
        if (astroids_.size() > astroidRotation_.size()) {
            astroidRotation_.resize(astroids_.size());
        }
    }
}

std::vector < std::pair < std::shared_ptr < Sprite > , std::shared_ptr < SpriteMaterial >>> & Astroid::getAstroids() {
    return astroids_;
}

std::vector < Vector2 > & Astroid::getAstroidSpeeds() {
    return astroidSpeeds_;
}

std::vector < float > & Astroid::getAstroidRotationSpeeds() {
    return astroidRotation_;
}

std::vector < float > & Astroid::getAstroidSize() {
    return astroidSize_;
}