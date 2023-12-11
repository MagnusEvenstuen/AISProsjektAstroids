#include "BaseObject.hpp"

Vector2& BaseObject::getObjectSpeed() {
    return objectSpeed_;
}

Vector3& BaseObject::getPosition() const {
    return sprite_.first->position;
}

std::shared_ptr<SpriteMaterial> BaseObject::getSpriteMaterial() const {
    return sprite_.second;
}

bool BaseObject::update(const float dt) {
    //Standard updating for all objects. They also have their own spesefic in terms of looping/deletion.
    Vector3& objectPosition = sprite_.first->position;
    objectPosition.x += objectSpeed_.x * dt * speedMultiplier_;
    objectPosition.y += objectSpeed_.y * dt * speedMultiplier_;
    return false;
}

std::shared_ptr<Sprite>& BaseObject::getSprite() {
    return sprite_.first;
}