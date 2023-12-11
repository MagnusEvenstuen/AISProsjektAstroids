#ifndef ASTROIDS_BASESHIP_HPP
#define ASTROIDS_BASESHIP_HPP

#include "Laser.hpp"

using namespace threepp;

class BaseShip : public BaseObject{
public:

    void moveShip(const float dt, const int boardSize);

    void updateLasers(const float dt, const std::shared_ptr<Scene>& scene);

    std::vector<Laser>& getLaser();

protected:
    std::vector<Laser> lasers_;
    int boardSize_;
};

#endif//ASTROIDS_BASESHIP_HPP
