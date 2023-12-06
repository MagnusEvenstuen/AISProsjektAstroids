#ifndef ASTROIDS_BASESHIP_HPP
#define ASTROIDS_BASESHIP_HPP

#include "BaseObject.hpp"
#include "Laser.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;

class BaseShip : public BaseObject{
public:

    void moveShip(const float dt, const int boardSize);

    void updateLasers(const float dt, std::shared_ptr<Scene> scene);

    std::vector<Laser>& getLaser();

protected:
    std::vector<Laser> lasers_;
    int boardSize_;
};

#endif//ASTROIDS_BASESHIP_HPP
