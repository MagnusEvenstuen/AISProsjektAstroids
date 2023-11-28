#ifndef ASTROIDS_COLLITIONDETECTION_HPP
#define ASTROIDS_COLLITIONDETECTION_HPP

#include "Explotion.hpp"

class CollitionDetection {
public:
    static void collitionChangeDirection(const std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& objects, std::vector<Vector2>& objectSpeeds, const float& objectHitBox){
        for (auto is = objects.begin(); is != objects.end(); ++is) {
            auto& astroid = *(is->first);
            for (int i = 0; i < objects.size(); i++) {
                if (objects[i].first->position.x + objectHitBox > astroid.position.x &&
                    objects[i].first->position.x < astroid.position.x + objectHitBox &&
                    objects[i].first->position.y + objectHitBox > astroid.position.y &&
                    objects[i].first->position.y < astroid.position.y + objectHitBox) {
                    if (i == std::distance(objects.begin(), is)) {
                        continue;
                    } else {
                        Vector2 collisonDirection(objects[i].first->position.x - objects[std::distance(objects.begin(), is)].first->position.x,
                                                  objects[i].first->position.y - objects[std::distance(objects.begin(), is)].first->position.y);
                        collisonDirection.normalize();
                        Vector2 speedI(objectSpeeds[i].x, objectSpeeds[i].y);
                        Vector2 speedAS(objectSpeeds[std::distance(objects.begin(), is)].x,
                                        objectSpeeds[std::distance(objects.begin(), is)].y);
                        objectSpeeds[i].x = speedAS.length() * collisonDirection[0];
                        objectSpeeds[i].y = speedAS.length() * collisonDirection[1];
                        objectSpeeds[std::distance(objects.begin(), is)].x = speedI.length() * -collisonDirection[0];
                        objectSpeeds[std::distance(objects.begin(), is)].y = speedI.length() * -collisonDirection[1];
                    }
                }
            }
        }
    }



    static int collitionDestroy(const std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& destroyers, std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& destroyds,
                          const float& destroyersHitBox, const float& destroydsHitBox, const std::shared_ptr<Scene>& scene, ExplotionCreator& explotionCreator, std::vector<Vector2>* destroydSpeeds = nullptr){
        int index = 0;
        int scoreChange = 0;
        for (auto is = destroyers.begin(); is != destroyers.end(); is++) {
            auto& destroyer = *(is->first);
            for (auto ds = destroyds.begin(); ds != destroyds.end();) {
                auto destroyd = *ds;

                if (destroyd.first->position.x + destroydsHitBox > destroyer.position.x &&
                    destroyd.first->position.x < destroyer.position.x + destroyersHitBox &&
                    destroyd.first->position.y + destroydsHitBox > destroyer.position.y &&
                    destroyd.first->position.y < destroyer.position.y + destroyersHitBox) {
                    if (destroydSpeeds != nullptr){
                        destroydSpeeds->erase(destroydSpeeds->begin() + index);
                    }
                    scoreChange += 1;
                    scene->remove(*destroyd.first);
                    ds = destroyds.erase(ds);
                    explotionCreator.createExpolotion(destroyd.first->position.x, destroyd.first->position.y);
                } else{
                    ds++;
                    index++;
                }
            }
            index = 0;
        }
        return scoreChange;
    }

    static int collitionDestroy(const std::vector<std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>>& destroyers, std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>>& destroyd,
                          const float& destroyersHitBox, const float& destroydsHitBox, int& score, ExplotionCreator& explotionCreator){
        for (auto is = destroyers.begin(); is != destroyers.end(); is++) {
            auto& destroyer = *(is->first);

            if (destroyd.first->position.x + destroydsHitBox > destroyer.position.x &&
                destroyd.first->position.x < destroyer.position.x + destroyersHitBox &&
                destroyd.first->position.y + destroydsHitBox > destroyer.position.y &&
                destroyd.first->position.y < destroyer.position.y + destroyersHitBox) {
                explotionCreator.createExpolotion(destroyd.first->position.x, destroyd.first->position.y);
                destroyd.first->position.x = 0;
                destroyd.first->position.y = 0;
                score = 0;
                return score;
            }
        }
        return score;
    }
};

#endif //ASTROIDS_COLLITIONDETECTION_HPP