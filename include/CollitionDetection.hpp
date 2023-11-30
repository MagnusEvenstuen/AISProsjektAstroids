#ifndef ASTROIDS_COLLITIONDETECTION_HPP
#define ASTROIDS_COLLITIONDETECTION_HPP

#include "threepp/threepp.hpp"
#include "Explotion.hpp"

using namespace threepp;

class CollitionDetection {
public: static void collitionChangeDirection(const std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& objects, std::vector<Vector2>& objectSpeeds, std::vector<float>& objectRotations, std::vector<float>& objectSize);

    static int collitionDestroy(const std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& destroyers, std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& destroyds,
                                const float& destroydsHitBox,  const float& destroyerHitBox, const std::shared_ptr<Scene>& scene, ExplotionCreator& explotionCreator, std::vector<Vector2>* destroydSpeeds = nullptr,
                                std::vector<float>* destroyedRotation = {});

    static int collitionDestroy(const std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& destroyers, std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& destroyds,
                                std::vector<float>& destroydsHitBox,  const float& destroyerHitBox,
                                const std::shared_ptr<Scene>& scene, ExplotionCreator& explotionCreator, std::vector<Vector2>* destroydSpeeds = nullptr,
                                std::vector<float>* destroyedRotation = {});

    static int collitionDestroy(const std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& destroyers, std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>& destroyd,
                                const float& destroyersHitBox, const float& destroydsHitBox, int& score);

    static int collitionDestroy(const std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& destroyers, std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>& destroyd,
                                const std::vector<float>& destroyersHitBox, const float& destroydsHitBox, int& score);
};

#endif //ASTROIDS_COLLITIONDETECTION_HPP