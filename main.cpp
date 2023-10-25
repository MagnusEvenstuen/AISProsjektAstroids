#include "controls.hpp"

using namespace threepp;

int main() {

    int creationTime = 1;
    double timePassed = creationTime + 1;

    Canvas canvas("threepp demo", {{"aa", 4}});
    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::black);

    auto camera = PerspectiveCamera::create();
    camera->position.z = 50;

    const std::shared_ptr<Scene> scene = Scene::create();   //Kode fra ChatGPT
    std::shared_ptr<Object> shipPtr = std::make_shared<Object>();
    shipPtr->setColor(Color::blue);
    scene->add(*shipPtr);   //Slutt kode fra ChatGPT


    Controls control(*shipPtr, scene);
    canvas.addKeyListener(&control);
    Astroid astroid;


    TextRenderer textRenderer;
    auto &textHandle = textRenderer.createHandle("Astroids");
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
            astroid.createAstroids(scene);
            timePassed = 0;
        }

        astroid.updateAstroids(scene, dt);

        control.setDeltaTime(dt);
        control.setSpeed();

        renderer.render(*scene, *camera);

        renderer.resetState();
        textRenderer.render();
    });
}