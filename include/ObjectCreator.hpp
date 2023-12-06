#ifndef ASTROIDS_OBJECTCREATOR_HPP
#define ASTROIDS_OBJECTCREATOR_HPP

#include "threepp/threepp.hpp"

using namespace threepp;
    class ObjectCreator: public Object3D {

    public: ObjectCreator();

        static std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>> createSprite(const float& sizeX,
                     const float& sizeY, const std::string& texture = "");

    private: std::shared_ptr<SphereGeometry> geometry_;
        std::shared_ptr<MeshBasicMaterial> material_;
        std::shared_ptr<Mesh> mesh_;
    };
#endif //ASTROIDS_OBJECTCREATOR_HPP