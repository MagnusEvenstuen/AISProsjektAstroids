#include "ObjectCreator.hpp"

using namespace threepp;

ObjectCreator::ObjectCreator() {
    geometry_ = SphereGeometry::create();
    material_ = MeshBasicMaterial::create();
    mesh_ = Mesh::create(geometry_, material_);

    add(mesh_);
}

std::pair<std::shared_ptr<Sprite>, std::shared_ptr<SpriteMaterial>> ObjectCreator::createSprite(const float& sizeX, const float& sizeY, const std::string& texture) {
    auto materialSprite = SpriteMaterial::create();
    if (!texture.empty()) {
        materialSprite->map = TextureLoader().load(texture);
        materialSprite->map->offset.set(0.5, 0.5);
    }
    auto sprite = Sprite::create(materialSprite);
    sprite->scale.set(sizeX, sizeY, 0);
    return {
            sprite,
            materialSprite};
}