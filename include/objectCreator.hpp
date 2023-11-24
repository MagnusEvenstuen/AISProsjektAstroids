#ifndef ASTROIDS_OBJECTCREATOR_HPP
#define ASTROIDS_OBJECTCREATOR_HPP

#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"

using namespace threepp;
namespace {
    class Object : public Object3D {

    public:
        Object() {
            geometry_ = SphereGeometry::create();
            material_ = MeshBasicMaterial::create();
            mesh_ = Mesh::create(geometry_, material_);

            add(mesh_);
        }

        void setColor(const Color &color) {

            material_->color.copy(color);
        }

        std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>> createSprite(const float& sizeX, const float& sizeY, const std::string& texture = ""){
            auto materialSprite = SpriteMaterial::create();
            if (!texture.empty()) {
                materialSprite->map = TextureLoader().load(texture);
                materialSprite->map->offset.set(0.5, 0.5);
            }
            auto sprite = Sprite::create(materialSprite);
            sprite->scale.set(sizeX, sizeY, 0);
            return {sprite, materialSprite};
        }

    private:
        std::shared_ptr<SphereGeometry> geometry_;
        std::shared_ptr<MeshBasicMaterial> material_;
        std::shared_ptr<Mesh> mesh_;
    };
}
#endif //ASTROIDS_OBJECTCREATOR_HPP
