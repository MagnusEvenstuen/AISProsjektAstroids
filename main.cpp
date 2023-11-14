#include "Controls.hpp"
#include "Astroid.hpp"
#include <string>
using namespace threepp;

int main() {

    const float creationTime = 0.5;
    double timePassed = creationTime + 1;
    std::string text = "Score: 0";

    Canvas canvas("Astroids", {{"aa", 4}});
    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::black);

    const auto camera = OrthographicCamera::create(-30, 30, 30, -30);
    camera->position.z = 50;

    const std::shared_ptr<Scene> scene = Scene::create();

    auto materialBackground = SpriteMaterial::create();
    materialBackground->map = TextureLoader().load("../textures/background.jpg");
    materialBackground->map->offset.set(0.5, 0.5);
    auto background = Sprite::create(materialBackground);
    background->scale.set(60, 60, 0);
    scene->add(background);

    auto materialShip = SpriteMaterial::create();
    materialShip->map = TextureLoader().load("../textures/Millenium Falcon.png");
    materialShip->map->offset.set(0.5, 0.5);
    auto ship = Sprite::create(materialShip);
    ship->scale.set(5, 5, 0);
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
        control.setSpeed(materialShip);

        renderer.render(*scene, *camera);

        text = "Score: " + std::to_string(astroid.getScore());
        textHandle.setText(text);

        renderer.resetState();
        textRenderer.render();
    });
}