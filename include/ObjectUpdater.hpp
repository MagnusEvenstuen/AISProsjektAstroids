#ifndef ASTROIDS_OBJECTUPDATER_HPP
#define ASTROIDS_OBJECTUPDATER_HPP


class ObjectUpdater {
public:

    static void moveObject(const std::shared_ptr<Sprite>& object, Vector2& objectSpeeds,
                           const float& dt, const float speedMultiplyer = 1){
        object->position.x += objectSpeeds[0] * speedMultiplyer * dt;
        object->position.y += objectSpeeds[1] * speedMultiplyer * dt;
    }

    static void loopObject(const std::shared_ptr<Sprite>& object, const int& boardSize){
        if (object->position.x > boardSize + 2 || object->position.x < -boardSize - 2){
            object->position.x *= -0.9;
        }
        if (object->position.y > boardSize + 2 || object->position.y < -boardSize - 2){
            object->position.y *= -0.9;
        }
    }

    static bool destroyObject(const std::shared_ptr<Sprite>& object, const int& boardSize, std::shared_ptr<Scene>& scene){
        if (object->position.x > boardSize + 2 || object->position.x < -boardSize - 2 || object->position.y > boardSize + 2 || object->position.y < -boardSize - 2) {
            scene->remove(*object);
            return true;
        } else{
            return false;
        }
    }
};
#endif//ASTROIDS_OBJECTUPDATER_HPP
