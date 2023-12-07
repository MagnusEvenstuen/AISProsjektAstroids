#ifndef ASTROIDS_EXPLOTIONCREATOR_HPP
#define ASTROIDS_EXPLOTIONCREATOR_HPP

#include "threepp/threepp.hpp"
#include "BaseObject.hpp"

using namespace threepp;

class ExplotionCreator : public BaseObject{
public:
    ExplotionCreator(std::shared_ptr<Scene>& scene, Vector3 position);

    bool update(const float& dt);

private:
    float yellow_ = 0.9f;
    Color explotionColor;
    std::shared_ptr<Scene> scene_;
};

#endif//ASTROIDS_EXPLOTIONCREATOR_HPP