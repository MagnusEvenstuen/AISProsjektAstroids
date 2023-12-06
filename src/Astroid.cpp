#include "Astroid.hpp"
#include "ObjectCreator.hpp"
#include <random>
#include <iostream>

Astroid::Astroid(const int& boardSize, const std::shared_ptr<Scene>& scene): boardSize_(boardSize) {
    //Creates astroids and assigns random values.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> size(3, 10);
    objectSize_ = size(gen);
    std::filesystem::path texturePath = __FILE__;
    texturePath = texturePath.parent_path().parent_path();
    texturePath += "/textures/Astroid.png";
    auto astroid = ObjectCreator::createSprite(objectSize_, objectSize_, texturePath.string());
    sprite_ = astroid;

    std::uniform_real_distribution <float> rotation(0, 3.14159265/2);
    objectRotationSpeed_ = rotation(gen);

    scene -> add(astroid.first);

    std::uniform_real_distribution <float> distribution(-1, 1);
    std::bernoulli_distribution chooseSign;

    for (int j = 0; j < 2; j++) {
        if (chooseSign(gen)) {
            sprite_.first -> position.x = chooseSign(gen) ? boardSize_ + 2 : -boardSize_ - 2;
            sprite_.first -> position.y = distribution(gen) * boardSize_ + 2;
        } else {
            sprite_.first -> position.y = chooseSign(gen) ? boardSize_ + 2 : -boardSize_ - 2;
            sprite_.first -> position.x = distribution(gen) * boardSize_ + 2;
        }
    }

    std::uniform_real_distribution<float> speedDistribution(minSpeed_, maxSpeed_);
    objectSpeed_[0] = speedDistribution(gen);
    objectSpeed_[1] = speedDistribution(gen);
}

void Astroid::checkAstroidCollition(std::vector<std::shared_ptr<Astroid>>& otherAstroids) {
    //Checks if two astroids collide.
    for (auto &otherAstroid : otherAstroids)
    {
        if (sprite_.first -> position.x > boardSize_ - 3 || sprite_.first -> position.x < -boardSize_ + 3 ||
            sprite_.first -> position.y > boardSize_ - 3 || sprite_.first -> position.y < -boardSize_ + 3){
            continue;
        }
        if (otherAstroid.get() != this) {
            const float otherAstroidSize = otherAstroid -> getObjectSize();
            Vector3 otherAstroidPosition = otherAstroid -> getPosition();
            Vector2 otherAstroidSpeed = otherAstroid -> getObjectSpeed();

            if (sqrt(pow(otherAstroidPosition.x - sprite_.first -> position.x, 2) + pow(otherAstroidPosition.y - sprite_.first -> position.y, 2))
                <= otherAstroidSize / 2 + objectSize_ / 2) {
                Vector2 collisonDirection(sprite_.first -> position.x - otherAstroidPosition.x,
                                          sprite_.first -> position.y - otherAstroidPosition.y);
                collisonDirection = collisonDirection.normalize();

                Vector2 speedSetter;

                objectSpeed_.x += (otherAstroidSize / objectSize_) * otherAstroidSpeed.x * collisonDirection[0] * 0.5;
                objectSpeed_.y += (otherAstroidSize / objectSize_) * otherAstroidSpeed.y * collisonDirection[1] * 0.5;
            }
        }
    }
}

bool Astroid::update(const float dt) {
    //Updates the position of the astroids.
    BaseObject::update(dt);
    const float objectRotation = objectRotationSpeed_;
    std::shared_ptr<SpriteMaterial> objectPicture = getSpriteMaterial();
    objectPicture->rotation += objectRotation * dt;
    if (sprite_.first->position.x > boardSize_ + objectSize_||
        sprite_.first->position.x < -boardSize_-  objectSize_||
        sprite_.first->position.y > boardSize_ + objectSize_||
        sprite_.first->position.y < -boardSize_ - objectSize_){
        scene_.remove(*sprite_.first);
        return true;
    }
    return false;
}

float& Astroid::getObjectSize() {
    return objectSize_;
}