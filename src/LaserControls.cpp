#include "LaserControls.hpp"
#include "ObjectCreator.hpp"
#include "ObjectUpdater.hpp"

using namespace threepp;

void LaserControls::setLaserSpeed(const float& speedX, const float& speedY) {
    laserSpeedX_ = speedX;
    laserSpeedY_ = speedY;
}

void LaserControls::createLaser(std::shared_ptr<Scene>& scene, const std::shared_ptr<Sprite>& obj) {
    auto laser = ObjectCreator::createSprite(1, 1);
    laser.second -> color = Color::red;
    lasers_.push_back(laser);
    scene -> add(lasers_.back().first);
    laser.first -> position.y = obj -> position.y;
    laser.first -> position.x = obj -> position.x;

    laserSpeeds_.emplace_back(laserSpeedX_, laserSpeedY_);
}

void LaserControls::updateLasers(std::shared_ptr<Scene>& scene, const float& dt, const int& boardSize) {
    for (long long i = 0; i < lasers_.size();) {
        ObjectUpdater::moveObject(lasers_[i].first, laserSpeeds_[i], dt, speedMultiplier_);
        bool destroyLaser = ObjectUpdater::destroyObject(lasers_[i].first, boardSize, scene);
        if (destroyLaser) {
            lasers_.erase(lasers_.begin() + i);
            laserSpeeds_.erase(laserSpeeds_.begin() + i);
        } else {
            i++;
        }
        if (lasers_.size() > laserSpeeds_.size()) {
            laserSpeeds_.resize(lasers_.size());
        }
    }
}

std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& LaserControls::getLasers() {
    return lasers_;
}