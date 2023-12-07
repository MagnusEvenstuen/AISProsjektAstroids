#include "BaseShip.hpp"

void BaseShip::moveShip(const float dt, const int boardSize) {
    if (sprite_.first->position.x > boardSize + 2 || sprite_.first->position.x < -boardSize - 2){
        sprite_.first->position.x *= -0.9;
    }

    if (sprite_.first->position.y > boardSize + 2 || sprite_.first->position.y < -boardSize - 2){
        sprite_.first->position.y *= -0.9;
    }
    BaseObject::update(dt);
}

void BaseShip::updateLasers(const float dt, std::shared_ptr<Scene> scene) {
    for (auto it = lasers_.begin(); it != lasers_.end();){
        auto laser = *it;
        bool remove = laser.update(dt, boardSize_);

        if (remove){
            scene ->remove(*laser.getSprite());
            it = lasers_.erase(it);
        } else{
            it++;
        }
    }
}

std::vector<Laser>& BaseShip::getLaser() {
    return lasers_;
}