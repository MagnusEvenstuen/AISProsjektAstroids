#include "Controls.hpp"
#include "Astroid.hpp"
#include <string>

using namespace threepp;

int main() {

    float creationTime = 0.5;
    double timePassed = creationTime + 1;
    std::string text = "Score: 0";

    Canvas canvas("Astroids", {{"aa", 4}});
    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::black);

    auto camera = PerspectiveCamera::create();
    camera->position.z = 50;

    const std::shared_ptr<Scene> scene = Scene::create();
    auto geometry = PlaneGeometry::create(5, 5);
    auto material = MeshBasicMaterial::create();
    material->map = TextureLoader().load("../textures/Millenium Falcon.png");
    auto ship = Mesh::create(geometry, material);
    scene->add(ship);


    Controls control(*ship, scene);
    canvas.addKeyListener(&control);
    Astroid astroid;


    TextRenderer textRenderer;
    auto &textHandle = textRenderer.createHandle(text);
    textHandle.verticalAlignment = threepp::TextHandle::VerticalAlignment::BOTTOM;
    textHandle.setPosition(0, canvas.size().height);
    textHandle.scale = 2;

    canvas.onWindowResize([&](WindowSize size) {
        camera->updateProjectionMatrix();
        renderer.setSize(size);
        textHandle.setPosition(0, size.height);
    });

    Clock clock;
    canvas.animate([&] {
        auto dt = clock.getDelta();
        timePassed += dt;

        if (timePassed > creationTime){
            astroid.createAstroids(scene, 30);
            timePassed -= creationTime;
        }

        astroid.updateAstroids(scene, dt);
        const auto& lasars = control.getLasars();
        astroid.checkColison(lasars, ship, scene);

        control.setDeltaTime(dt);
        control.setSpeed();

        renderer.render(*scene, *camera);

        text = "Score: " + std::to_string(astroid.getScore());
        textHandle.setText(text);

        renderer.resetState();
        textRenderer.render();
    });
}