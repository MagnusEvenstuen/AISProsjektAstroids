#ifndef ASTROIDS_LASERCONTROLS_HPP
#define ASTROIDS_LASERCONTROLS_HPP

#include "ObjectCreator.hpp"
#include "ObjectUpdater.hpp"

using namespace threepp;
namespace {
    class LaserControls {
    public:
        void setLaserSpeed(const float speedX, const float speedY) {
            laserSpeedX_ = speedX;
            laserSpeedY_ = speedY;
        }

        void createLaser(std::shared_ptr<Scene>& scene, const std::shared_ptr<Sprite>& obj) {
            auto laser = Object3D.createSprite(1, 1);
            laser.second->color = Color::red;
            lasers_.push_back(laser);
            scene->add(lasers_.back().first);
            laser.first->position.y = obj->position.y;
            laser.first->position.x = obj->position.x;

            laserSpeeds_.emplace_back(laserSpeedX_, laserSpeedY_);
        }

        void updateLasers(std::shared_ptr<Scene>& scene, const float dt, const int& boardSize) {
            for (long long i = 0; i < lasers_.size();) {
                ObjectUpdater::moveObject(lasers_[i].first, laserSpeeds_[i], dt,speedMultiplier_);
                bool destroyLaser = ObjectUpdater::destroyObject(lasers_[i].first, boardSize, scene);
                if (destroyLaser) {
                    lasers_.erase(lasers_.begin() + i);
                    laserSpeeds_.erase(laserSpeeds_.begin() + i);
                } else {
                    i++;
                }
            }
        }

        std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& getLasers() {
            return lasers_;
        }

    private:
        float laserSpeedX_ = 0;
        float laserSpeedY_ = 0;
        const float speedMultiplier_ = 60;
        std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>> lasers_;
        std::vector<Vector2> laserSpeeds_;
        ObjectCreator Object3D;
    };
}
#endif //ASTROIDS_LASERCONTROLS_HPP
