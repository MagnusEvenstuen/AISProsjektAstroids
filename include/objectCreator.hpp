#ifndef PLACEHOLDER_OBJECTCREATOR_HPP
#define PLACEHOLDER_OBJECTCREATOR_HPP

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

        std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>> createSprite(const std::string& texture, const float& sizeX, const float& sizeY, const float& sizeZ = 0){
            auto materialSprite = SpriteMaterial::create();
            materialSprite->map = TextureLoader().load(texture);
            materialSprite->map->offset.set(0.5, 0.5);
            auto sprite = Sprite::create(materialSprite);
            sprite->scale.set(sizeX, sizeY, sizeZ);
            return {sprite, materialSprite};
        }

    private:
        std::shared_ptr<SphereGeometry> geometry_;
        std::shared_ptr<MeshBasicMaterial> material_;
        std::shared_ptr<Mesh> mesh_;
    };
}
#endif //PLACEHOLDER_OBJECTCREATOR_HPP
