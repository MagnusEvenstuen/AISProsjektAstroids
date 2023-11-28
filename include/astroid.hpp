#ifndef ASTROIDS_ASTROID_HPP
#define ASTROIDS_ASTROID_HPP

#include "ObjectCreator.hpp"

class Astroid{
public:
    Astroid(const int& boardSize) : boardSize_(boardSize) {
    }
    void createAstroids(const std::shared_ptr<Scene>& scene);

    void updateAstroids(std::shared_ptr<Scene>& scene, const float dt);


    std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& getAstroids();

    std::vector<Vector2>& getAstroidSpeeds();

private:
    std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>> astroids_;
    std::vector<Vector2> astroidSpeeds_;
    ObjectCreator Object3D;
    Scene scene_;
    int boardSize_;
    const int minSpeed_ = -20;
    const int maxSpeed_ = 20;
};

#endif //ASTROIDS_ASTROID_HPP