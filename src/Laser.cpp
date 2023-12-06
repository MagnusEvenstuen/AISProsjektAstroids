#include "Laser.hpp"
#include "ObjectCreator.hpp"

using namespace threepp;

Laser::Laser(const Vector2& direction, const Vector3& position, std::shared_ptr<Scene>& scene) {
    //Creation of the laser.
    sprite_ = ObjectCreator::createSprite(1, 1);
    sprite_.second -> color = Color::red;
    scene -> add(sprite_.first);

    sprite_.first -> position.x = position.x;
    sprite_.first -> position.y = position.y;

    speedMultiplier_ = 60;
    objectSpeed_ = direction;
}

bool Laser::update(const float& dt, const int& boardSize) {
    //The function to update the laser.
    if (sprite_.first -> position.x > boardSize || sprite_.first -> position.x < -boardSize ||
        sprite_.first -> position.y > boardSize || sprite_.first -> position.y < -boardSize){
        return true;
    } else{
        BaseObject::update(dt);
        return false;
    }
}

std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>& Laser::getLasers() {
    return sprite_;
}