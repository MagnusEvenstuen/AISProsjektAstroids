#define _USE_MATH_DEFINES

#include "Controls.hpp"
#include "ObjectCreator.hpp"
#include "ObjectUpdater.hpp"
#include "LaserControls.hpp"
#include <cmath>

using namespace threepp;

void Controls::onKeyPressed(const KeyEvent evt) {
    if (evt.key == Key::W || evt.key == Key::UP) {
        speed_ = 1;
    }
    if (evt.key == Key::A || evt.key == Key::LEFT) {
        leftPressed_ = true;
    }
    if (evt.key == Key::D || evt.key == Key::RIGHT) {
        rightPressed_ = true;
    }
    if (evt.key == Key::SPACE) {
        laserControls_.createLaser(scene_, obj_.first);
    }
}

void Controls::onKeyReleased(const KeyEvent evt) {
    if (evt.key == Key::W || evt.key == Key::UP) {
        speed_ = 0;
    }
    if (evt.key == Key::A || evt.key == Key::LEFT) {
        leftPressed_ = false;
    }
    if (evt.key == Key::D || evt.key == Key::RIGHT) {
        rightPressed_ = false;
    }
}

std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& Controls::getLasers() {
    return laserControls_.getLasers();
}

void Controls::setDeltaTime(const float dt) {
    dt_ = dt;
}

void Controls::setSpeed() {
    obj_.second -> rotation += (leftPressed_ - rightPressed_) * dt_ * M_PI / 180 * 200;
    obj_.first -> rotation.z += (leftPressed_ - rightPressed_) * dt_ * M_PI / 180 * 200;
    Vector2 direction(cos(obj_.first -> rotation.z()), sin(obj_.first -> rotation.z()));

    ObjectUpdater::moveObject(obj_.first, direction, dt_, speedMultiplier_ * speed_);
    ObjectUpdater::loopObject(obj_.first, boardSize_);

    laserControls_.setLaserSpeed(direction[0], direction[1]);
    laserControls_.updateLasers(scene_, dt_, boardSize_);
}
