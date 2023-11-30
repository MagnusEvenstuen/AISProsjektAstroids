#ifndef ASTROIDS_EXPLOTION_HPP
#define ASTROIDS_EXPLOTION_HPP

#include "threepp/threepp.hpp"

using namespace threepp;

class ExplotionCreator {
public:
    ExplotionCreator(std::shared_ptr<Scene>& scene) : explotionColor(255, 0, 0), scene_(scene) {
    }

    void createExpolotion(const float& xPos, const float& yPos);

    void moveExplotion(const float& dt);

private:
    std::vector<float> yellow_;
    Color explotionColor;
    std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>> explotionParticles_;
    std::vector<Vector2> explotionParticleSpeeds_;
    std::shared_ptr<Scene> scene_;
};

#endif //ASTROIDS_EXPLOTION_HPP