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

    private:
        std::shared_ptr<SphereGeometry> geometry_;
        std::shared_ptr<MeshBasicMaterial> material_;
        std::shared_ptr<Mesh> mesh_;
    };
}
#endif //PLACEHOLDER_OBJECTCREATOR_HPP
