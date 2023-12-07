#include "ExplotionCreator.hpp"
#include "ObjectCreator.hpp"
#include <random>

ExplotionCreator::ExplotionCreator(std::shared_ptr<Scene>& scene, Vector3 position): explotionColor(1, 0.9, 0), scene_(scene) {
    //Creation of explotion particles, they are given random speed.
    std::random_device rd;
    std::mt19937 gen(rd());
    sprite_ = ObjectCreator::createSprite(1, 1);
    sprite_.second -> color = explotionColor;
    scene_ -> add(sprite_.first);
    sprite_.first -> position.y = position.y;
    sprite_.first -> position.x = position.x;

    std::uniform_real_distribution<float> speedDistribution(-4, 4);
    objectSpeed_.x = speedDistribution(gen);
    objectSpeed_.y = speedDistribution(gen);
}


bool ExplotionCreator::update(const float& dt) {
    //The function for updating explotion particles.
    yellow_ -= 1.0f * dt;
    sprite_.first -> scale.x -= 1 * dt;
    sprite_.first -> scale.y -= 1 * dt;
    explotionColor = Color(1, yellow_, 0);
    sprite_.second -> color = explotionColor;
    BaseObject::update(dt);
    if (sprite_.first -> scale.x < 0 || sprite_.first -> scale.y < 0) {
        return true;
    } else{
        return false;
    }
}