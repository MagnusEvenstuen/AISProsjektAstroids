#ifndef ASTROIDS_LASER_HPP
#define ASTROIDS_LASER_HPP

#include "threepp/threepp.hpp"
#include "BaseObject.hpp"
#include "ObjectCreator.hpp"

using namespace threepp;

class Laser : public BaseObject{
public: Laser(const Vector2& direction, const Vector3& position, std::shared_ptr<Scene>& scene);

    bool Laser::update(const float& dt, const int& boardSize);

    std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>& getLasers();

private:
    std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>> lasers_;
};
#endif//ASTROIDS_LASER_HPP