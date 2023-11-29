#ifndef ASTROIDS_COLLITIONDETECTION_HPP
#define ASTROIDS_COLLITIONDETECTION_HPP

#include "Explotion.hpp"
#include "ObjectCreator.hpp"
#include "Game.hpp"

class CollitionDetection {
public: static void collitionChangeDirection(const std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& objects, std::vector<Vector2>& objectSpeeds, std::vector<float>& objectRotations, std::vector<float>& objectSize) {
        for (auto is = objects.begin(); is != objects.end(); ++is) {
            auto & object = * (is -> first);
            for (int i = 0; i < objects.size(); i++) {
                if (objects[i].first -> position.x + objectSize[std::distance(objects.begin(), is)] - objectSize[std::distance(objects.begin(), is)] / 3 > object.position.x &&
                    objects[i].first -> position.x < object.position.x + objectSize[i] - objectSize[std::distance(objects.begin(), is)] / 3 &&
                    objects[i].first -> position.y + objectSize[std::distance(objects.begin(), is)] - objectSize[std::distance(objects.begin(), is)] / 3 > object.position.y &&
                    objects[i].first -> position.y < object.position.y + objectSize[i] - objectSize[std::distance(objects.begin(), is)] / 3) {
                    if (i == std::distance(objects.begin(), is)) {
                        continue;
                    } else {
                        Vector2 collisonDirection(objects[i].first -> position.x - objects[std::distance(objects.begin(), is)].first -> position.x,
                                                  objects[i].first -> position.y - objects[std::distance(objects.begin(), is)].first -> position.y);
                        collisonDirection.normalize();
                        Vector2 speedI(objectSpeeds[i].x, objectSpeeds[i].y);
                        Vector2 speedAS(objectSpeeds[std::distance(objects.begin(), is)].x,
                                        objectSpeeds[std::distance(objects.begin(), is)].y);
                        if (objectSize[i] > (objectSize[std::distance(objects.begin(), is)])) {
                            objectSpeeds[i].x = speedAS.length() * collisonDirection[0] * (objectSize[std::distance(objects.begin(), is)] / objectSize[i]);
                            objectSpeeds[i].y = speedAS.length() * collisonDirection[1] * (objectSize[std::distance(objects.begin(), is)] / objectSize[i]);
                            objectSpeeds[std::distance(objects.begin(), is)].x = speedI.length() * -collisonDirection[0] * (objectSize[i] / objectSize[std::distance(objects.begin(), is)]);
                            objectSpeeds[std::distance(objects.begin(), is)].y = speedI.length() * -collisonDirection[1] * (objectSize[i] / objectSize[std::distance(objects.begin(), is)]);
                        } else {
                            objectSpeeds[i].x = speedAS.length() * collisonDirection[0] * (objectSize[i] / objectSize[std::distance(objects.begin(), is)]);
                            objectSpeeds[i].y = speedAS.length() * collisonDirection[1] * (objectSize[i] / objectSize[std::distance(objects.begin(), is)]);
                            objectSpeeds[std::distance(objects.begin(), is)].x = speedI.length() * -collisonDirection[0] * (objectSize[std::distance(objects.begin(), is)] / objectSize[i]);
                            objectSpeeds[std::distance(objects.begin(), is)].y = speedI.length() * -collisonDirection[1] * (objectSize[std::distance(objects.begin(), is)] / objectSize[i]);
                        }
                        float objectRotation = objectRotations[i];
                        objectRotations[i] = objectRotations[std::distance(objects.begin(), is)];
                        objectRotations[std::distance(objects.begin(), is)] = objectRotation;
                    }
                }
            }
        }
    }

    static int collitionDestroy(const std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& destroyers, std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& destroyds,
                                const float& destroydsHitBox, const std::shared_ptr<Scene>& scene, ExplotionCreator& explotionCreator, std::vector<Vector2>* destroydSpeeds = nullptr,
                                std::vector<float>* destroyedRotation = {}) {
        std::vector<float> destroydsHitBoxes(destroyds.size(), destroydsHitBox);
        return collitionDestroy(destroyers, destroyds, destroydsHitBoxes, scene, explotionCreator, destroydSpeeds, destroyedRotation);
    }

    static int collitionDestroy(const std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& destroyers, std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& destroyds,
                                std::vector<float>& destroydsHitBox,
                                const std::shared_ptr<Scene>& scene, ExplotionCreator& explotionCreator, std::vector<Vector2>* destroydSpeeds = nullptr,
                                std::vector<float>* destroyedRotation = {}) {
        int index = 0;
        int scoreChange = 0;
        for (auto is = destroyers.begin(); is != destroyers.end(); is++) {
            auto & destroyer = * (is -> first);
            for (auto ds = destroyds.begin(); ds != destroyds.end();) {
                auto destroyd = * ds;

                if (destroyd.first -> position.x + destroydsHitBox[std::distance(destroyds.begin(), ds)] - destroydsHitBox[std::distance(destroyds.begin(), ds)] / 3 > destroyer.position.x &&
                    destroyd.first -> position.x < destroyer.position.x + destroydsHitBox[std::distance(destroyds.begin(), ds)] - destroydsHitBox[std::distance(destroyds.begin(), ds)] / 3 &&
                    destroyd.first -> position.y + destroydsHitBox[std::distance(destroyds.begin(), ds)] - destroydsHitBox[std::distance(destroyds.begin(), ds)] / 3 > destroyer.position.y &&
                    destroyd.first -> position.y < destroyer.position.y + destroydsHitBox[std::distance(destroyds.begin(), ds)] - destroydsHitBox[std::distance(destroyds.begin(), ds)] / 3) {
                    if (destroydSpeeds != nullptr) {
                        destroydSpeeds -> erase(destroydSpeeds -> begin() + index);
                        if (!destroyedRotation -> empty()) {
                            destroyedRotation -> erase((destroyedRotation -> begin() + index));
                        }
                    }
                    scoreChange += 1;
                    scene -> remove( * destroyd.first);
                    ds = destroyds.erase(ds);
                    explotionCreator.createExpolotion(destroyd.first -> position.x, destroyd.first -> position.y);
                } else {
                    ds++;
                    index++;
                }
            }
            index = 0;
        }
        return scoreChange;
    }

    static int collitionDestroy(const std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& destroyers, std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>& destroyd,
                                const float& destroyersHitBox, int& score) {
        std::vector<float>destroyersHitBoxes(destroyers.size(), destroyersHitBox);
        return collitionDestroy(destroyers, destroyd, destroyersHitBoxes, score);
    }

    static int collitionDestroy(const std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& destroyers, std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>& destroyd,
                                const std::vector<float>& destroyersHitBox, int& score) {
        for (auto is = destroyers.begin(); is != destroyers.end(); is++) {
            auto & destroyer = * (is -> first);

            if (destroyd.first -> position.x + destroyersHitBox[std::distance(destroyers.begin(), is)] - destroyersHitBox[std::distance(destroyers.begin(), is)] / 3 > destroyer.position.x &&
                destroyd.first -> position.x < destroyer.position.x + destroyersHitBox[std::distance(destroyers.begin(), is)] - destroyersHitBox[std::distance(destroyers.begin(), is)] / 3 &&
                destroyd.first -> position.y + destroyersHitBox[std::distance(destroyers.begin(), is)] - destroyersHitBox[std::distance(destroyers.begin(), is)] / 3 > destroyer.position.y &&
                destroyd.first -> position.y < destroyer.position.y + destroyersHitBox[std::distance(destroyers.begin(), is)] - destroyersHitBox[std::distance(destroyers.begin(), is)] / 3) {
                destroyd.first = nullptr;
                destroyd.second = nullptr;
                score = 0;
                return score;
            }
        }
        return score;
    }
};

#endif //ASTROIDS_COLLITIONDETECTION_HPP