#include "ObjectUpdater.hpp"

void ObjectUpdater::moveObject(const std::shared_ptr<Sprite>& object, Vector2& objectSpeeds, const float& dt, const float speedMultiplyer) {
    object->position.x += objectSpeeds[0] * speedMultiplyer * dt;
    object->position.y += objectSpeeds[1] * speedMultiplyer * dt;
}

void ObjectUpdater::loopObject(const std::shared_ptr<Sprite>& object, const int& boardSize) {
    if (object->position.x > boardSize + 2 || object->position.x < -boardSize - 2){
        object->position.x *= -0.9;
    }
    if (object->position.y > boardSize + 2 || object->position.y < -boardSize - 2){
        object->position.y *= -0.9;
    }
}

bool ObjectUpdater::destroyObject(const std::shared_ptr<Sprite>& object, const int& boardSize, std::shared_ptr<Scene>& scene) {
    if (object->position.x > boardSize + 2 || object->position.x < -boardSize - 2 || object->position.y > boardSize + 2 || object->position.y < -boardSize - 2) {
        scene->remove(*object);
        return true;
    } else{
        return false;
    }
}