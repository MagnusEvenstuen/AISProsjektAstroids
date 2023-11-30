#ifndef ASTROIDS_LASERCONTROLS_HPP
#define ASTROIDS_LASERCONTROLS_HPP

#include "threepp/threepp.hpp"

using namespace threepp;

class LaserControls {
public: void setLaserSpeed(const float& speedX, const float& speedY);

    void createLaser(std::shared_ptr<Scene>& scene, const std::shared_ptr<Sprite>& obj);

    void updateLasers(std::shared_ptr<Scene>& scene, const float& dt, const int& boardSize);

    std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& getLasers();

private: float laserSpeedX_ = 0;
    float laserSpeedY_ = 0;
    const float speedMultiplier_ = 60;
    std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>> lasers_;
    std::vector<Vector2> laserSpeeds_;
};
#endif //ASTROIDS_LASERCONTROLS_HPP