#include "controls.hpp"

using namespace threepp;

int main() {

    Canvas canvas("threepp demo", {{"aa", 4}});
    GLRenderer renderer(canvas.size());
    renderer.setClearColor(Color::black);

    auto camera = PerspectiveCamera::create();
    camera->position.z = 50;

    OrbitControls controls{*camera, canvas};

    const std::shared_ptr<Scene> scene = Scene::create();   //Kode fra ChatGPT
    std::shared_ptr<Object> shipPtr = std::make_shared<Object>();
    shipPtr->setColor(Color::blue);
    scene->add(*shipPtr);   //Slutt kode fra ChatGPT


    Controls control(*shipPtr, scene);
    canvas.addKeyListener(&control);


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
        control.setDeltaTime(dt);
        control.setSpeed();

        renderer.render(*scene, *camera);

        renderer.resetState();// needed when using TextRenderer
        textRenderer.render();
    });
}