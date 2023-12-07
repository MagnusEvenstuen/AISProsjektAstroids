#ifndef ASTROIDS_ASTROID_HPP
#define ASTROIDS_ASTROID_HPP

#include "BaseObject.hpp"
#include "threepp/threepp.hpp"


using namespace threepp;

class Astroid : public BaseObject {
public:
    Astroid(const int& boardSize, const std::shared_ptr<Scene>& scene);

    void checkAstroidCollition(std::vector<std::shared_ptr<Astroid>>& otherAstroids);

    bool update(const float dt) override;

    float& getObjectSize();;

private:
    Scene scene_;
    int boardSize_;
    const float minSpeed_ = -20;
    const float maxSpeed_ = 20;
    float objectRotationSpeed_ = 0;
    float objectSize_ = 0;
};

#endif //ASTROIDS_ASTROID_HPP