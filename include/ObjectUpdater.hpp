#ifndef ASTROIDS_OBJECTUPDATER_HPP
#define ASTROIDS_OBJECTUPDATER_HPP

#include "ObjectCreator.hpp"

class ObjectUpdater {
public:

    static void moveObject(const std::shared_ptr<Sprite>& object, Vector2& objectSpeeds,
                           const float& dt, const float speedMultiplyer = 1);

    static void loopObject(const std::shared_ptr<Sprite>& object, const int& boardSize);

    static bool destroyObject(const std::shared_ptr<Sprite>& object, const int& boardSize, std::shared_ptr<Scene>& scene);
};
#endif//ASTROIDS_OBJECTUPDATER_HPP