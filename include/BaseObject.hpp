#ifndef ASTROIDS_BASEOBJECT_HPP
#define ASTROIDS_BASEOBJECT_HPP

#include "threepp/threepp.hpp"

using namespace threepp;

class BaseObject{
public:

    Vector2& getObjectSpeed();

    float& getObjectRotationSpeed();

    std::shared_ptr<Sprite>& getSprite();

    Vector3& getPosition();

    std::shared_ptr<SpriteMaterial> getSpriteMaterial();

    virtual bool update(const float dt);


protected:
    Vector2 objectSpeed_;
    float speedMultiplier_ = 1;
    std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>> sprite_;
};
#endif//ASTROIDS_BASEOBJECT_HPP
