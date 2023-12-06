#define _USE_MATH_DEFINES

#include "Ship.hpp"
#include <cmath>

using namespace threepp;

Ship::Ship(std::shared_ptr<Scene>& scene, const int boardSize): scene_(scene) {
    //Creation of the ship.
    boardSize_ = boardSize;
    std::filesystem::path texturePath = __FILE__;
    texturePath = texturePath.parent_path().parent_path();
    texturePath += "/textures/Millenium Falcon.png";
    sprite_ = ObjectCreator::createSprite(5, 5, texturePath.string());

    scene_ -> add(sprite_.first);
    speedMultiplier_ = 0;
}


void Ship::onKeyPressed(const KeyEvent evt) {
    //What to do when keys are pressed.
    if (evt.key == Key::W || evt.key == Key::UP) {
        speedMultiplier_ = 15;
    }
    if (evt.key == Key::A || evt.key == Key::LEFT) {
        leftPressed_ = true;
    }
    if (evt.key == Key::D || evt.key == Key::RIGHT) {
        rightPressed_ = true;
    }
    if (evt.key == Key::SPACE) {
        lasers_.emplace_back(objectSpeed_, sprite_.first -> position, scene_);
    }
}

void Ship::onKeyReleased(const KeyEvent evt) {
    //Reset to standard when keys are releasd.
    if (evt.key == Key::W || evt.key == Key::UP) {
        speedMultiplier_ = 0;
    }
    if (evt.key == Key::A || evt.key == Key::LEFT) {
        leftPressed_ = false;
    }
    if (evt.key == Key::D || evt.key == Key::RIGHT) {
        rightPressed_ = false;
    }
}

void Ship::move(const float dt) {
    //Updating the ship.
    sprite_.second -> rotation += (leftPressed_ - rightPressed_) * M_PI / 180 * 200 * dt;
    sprite_.first -> rotation.z += (leftPressed_ - rightPressed_) * M_PI / 180 * 200 * dt;

    Vector2 direction(cos(sprite_.first -> rotation.z()), sin(sprite_.first -> rotation.z()));
    objectSpeed_ = direction;

    BaseShip::updateLasers(dt, scene_);

    BaseShip::moveShip(dt, boardSize_);
}
