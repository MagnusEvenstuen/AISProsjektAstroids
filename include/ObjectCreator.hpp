#ifndef ASTROIDS_OBJECTCREATOR_HPP
#define ASTROIDS_OBJECTCREATOR_HPP

#include "threepp/threepp.hpp"

using namespace threepp;
    class ObjectCreator: public Object3D {

    public:
        static std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>> createSprite(const float& sizeX,
                     const float& sizeY, const std::string& texture = "");

    };
#endif //ASTROIDS_OBJECTCREATOR_HPP